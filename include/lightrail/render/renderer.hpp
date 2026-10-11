#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "lightrail/camera/camera.hpp"
#include "lightrail/image/color.hpp"
#include "lightrail/image/image.hpp"
#include "lightrail/math/constants.hpp"
#include "lightrail/scene/scene.hpp"

namespace lightrail {

class Renderer {
public:
    int max_depth{5}; // Maximum recursion depth for reflective rays
    int samples_per_pixel{1}; // 1 for fast preview, higher for anti-aliasing

    Renderer() = default;

    Image render(const Scene& scene, Camera& camera, int width, int height) const {
        camera.initialize_for_resolution(width, height);
        Image image(width, height);

        auto start_time = std::chrono::high_resolution_clock::now();
        std::cout << "Rendering " << width << "x" << height
                  << " (max depth: " << max_depth << ")... " << std::flush;

        // Modern C++ multithreading: divide rows among CPU hardware threads
        const unsigned int num_threads = std::max(1u, std::thread::hardware_concurrency());
        std::vector<std::thread> workers;
        workers.reserve(num_threads);

        const int rows_per_thread = (height + num_threads - 1) / num_threads;

        for (unsigned int t = 0; t < num_threads; ++t) {
            int y_start = t * rows_per_thread;
            int y_end = std::min(height, y_start + rows_per_thread);

            if (y_start >= height) break;

            workers.emplace_back([this, &scene, &camera, &image, width, y_start, y_end]() {
                for (int y = y_start; y < y_end; ++y) {
                    for (int x = 0; x < width; ++x) {
                        Ray ray = camera.get_ray(x, y);
                        Color pixel_color = trace_ray(ray, scene, max_depth);
                        image.set(x, y, pixel_color);
                    }
                }
            });
        }

        for (auto& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << "DONE in " << elapsed.count() << " seconds (" << num_threads << " threads).\n";

        return image;
    }

private:
    Color trace_ray(const Ray& r, const Scene& scene, int depth) const {
        // Exceeded recursion depth: terminate ray bounce
        if (depth <= 0) {
            return Color::black();
        }

        HitRecord rec;
        // Check for ray hit (0.001 minimum t avoids shadow acne / self-intersection)
        if (!scene.hit(r, 0.001, kInfinity, rec)) {
            return scene.background_color;
        }

        const auto& mat = *rec.material;
        Color hit_color = mat.albedo;

        // 1. Ambient lighting term
        Color direct_light = mat.ka * (hit_color * scene.ambient_light);

        // 2. Direct illumination from lights (Diffuse + Blinn-Phong Specular)
        for (const auto& light : scene.lights) {
            Vec3 light_dir;
            double light_dist = kInfinity;

            if (light.type == LightType::Point) {
                Vec3 to_light = light.position - rec.point;
                light_dist = to_light.length();
                light_dir = to_light / light_dist;
            } else {
                light_dir = -light.direction;
            }

            // Shadow ray check
            Ray shadow_ray(rec.point + rec.normal * 0.001, light_dir);
            HitRecord shadow_rec;
            bool in_shadow = scene.hit(shadow_ray, 0.001, light_dist - 0.001, shadow_rec);

            if (!in_shadow) {
                // Diffuse (Lambertian)
                double n_dot_l = std::max(0.0, dot(rec.normal, light_dir));
                Color diffuse = mat.kd * n_dot_l * (hit_color * light.intensity);

                // Specular (Blinn-Phong)
                Vec3 view_dir = -r.direction;
                Vec3 half_vec = unit_vector(light_dir + view_dir);
                double n_dot_h = std::max(0.0, dot(rec.normal, half_vec));
                double spec = std::pow(n_dot_h, mat.shininess);
                Color specular = mat.ks * spec * light.intensity;

                direct_light += diffuse + specular;
            }
        }

        // 3. Recursive mirror reflections
        if (mat.reflectivity > 0.0 && depth > 0) {
            Vec3 reflect_dir = reflect(r.direction, rec.normal);
            Ray reflect_ray(rec.point + rec.normal * 0.001, reflect_dir);
            Color reflected_color = trace_ray(reflect_ray, scene, depth - 1);

            return (1.0 - mat.reflectivity) * direct_light + mat.reflectivity * reflected_color;
        }

        return direct_light;
    }
};

} // namespace lightrail
