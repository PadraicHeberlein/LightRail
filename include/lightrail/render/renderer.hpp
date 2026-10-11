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
    int max_depth{5};         // Maximum recursion depth for reflective/refractive rays
    int samples_per_pixel{1}; // >1 enables anti-aliasing via stochastic super-sampling

    Renderer() = default;

    Image render(const Scene& scene, Camera& camera, int width, int height) const {
        camera.initialize_for_resolution(width, height);
        Image image(width, height);

        auto start_time = std::chrono::high_resolution_clock::now();
        std::cout << "Rendering " << width << "x" << height
                  << " (SPP: " << samples_per_pixel
                  << ", Depth: " << max_depth << ")... " << std::flush;

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
                        Color pixel_color(0.0, 0.0, 0.0);

                        for (int s = 0; s < samples_per_pixel; ++s) {
                            bool jitter = (samples_per_pixel > 1);
                            Ray ray = camera.get_ray(x, y, jitter);
                            pixel_color += trace_ray(ray, scene, max_depth);
                        }

                        image.set(x, y, (1.0 / samples_per_pixel) * pixel_color);
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
        if (depth <= 0) {
            return Color::black();
        }

        HitRecord rec;
        if (!scene.hit(r, 0.001, kInfinity, rec)) {
            return scene.background_color;
        }

        const auto& mat = *rec.material;

        // ---------------------------------------------------------
        // Enhancement 2: Glass & Dielectric Refraction / Fresnel
        // ---------------------------------------------------------
        if (mat.type == MaterialType::Dielectric) {
            double refraction_ratio = rec.front_face ? (1.0 / mat.ior) : mat.ior;
            Vec3 unit_dir = unit_vector(r.direction);

            double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
            double sin_theta = std::sqrt(std::abs(1.0 - cos_theta * cos_theta));

            bool cannot_refract = (refraction_ratio * sin_theta > 1.0);
            Vec3 ray_out_dir;

            // Total Internal Reflection OR Schlick Fresnel reflection
            if (cannot_refract || Material::reflectance(cos_theta, refraction_ratio) > random_double()) {
                ray_out_dir = reflect(unit_dir, rec.normal);
                Ray reflect_ray(rec.point + rec.normal * 0.001, ray_out_dir);
                return mat.albedo * trace_ray(reflect_ray, scene, depth - 1);
            } else {
                ray_out_dir = refract(unit_dir, rec.normal, refraction_ratio);
                // Step through surface inside or outside
                Point3 ray_orig = rec.point - (rec.normal * 0.001);
                Ray refract_ray(ray_orig, ray_out_dir);
                return mat.albedo * trace_ray(refract_ray, scene, depth - 1);
            }
        }

        // ---------------------------------------------------------
        // Phong / Specular Illumination Model with Shadows
        // ---------------------------------------------------------
        Color hit_color = mat.albedo;
        Color direct_light = mat.ka * (hit_color * scene.ambient_light);

        // ---------------------------------------------------------
        // Enhancement 5: Soft Shadows & Area Lights
        // ---------------------------------------------------------
        for (const auto& light : scene.lights) {
            int num_samples = std::max(1, light.shadow_samples);
            Color light_accum = Color::black();

            for (int s = 0; s < num_samples; ++s) {
                Point3 light_sample_pos = light.sample_point();
                Vec3 light_dir;
                double light_dist = kInfinity;

                if (light.type == LightType::Point || light.type == LightType::Area) {
                    Vec3 to_light = light_sample_pos - rec.point;
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

                    light_accum += (diffuse + specular);
                }
            }

            direct_light += (1.0 / num_samples) * light_accum;
        }

        // Recursive mirror reflections
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
