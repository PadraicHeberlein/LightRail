#include <iostream>
#include <memory>
#include <stdexcept>
#include "lightrail/camera/camera.hpp"
#include "lightrail/image/color.hpp"
#include "lightrail/material/material.hpp"
#include "lightrail/math/constants.hpp"
#include "lightrail/math/vec3.hpp"
#include "lightrail/render/renderer.hpp"
#include "lightrail/scene/mesh.hpp"
#include "lightrail/scene/plane.hpp"
#include "lightrail/scene/scene.hpp"
#include "lightrail/scene/sphere.hpp"
#include "lightrail/scene/triangle.hpp"

using namespace lightrail;

int main() {
    std::cout << "========================================\n";
    std::cout << "  LightRail C++ Ray Tracer Engine       \n";
    std::cout << "========================================\n";

    try {
        // 1. Construct Scene
        Scene scene;
        scene.ambient_light = Color(0.12, 0.12, 0.15);
        scene.background_color = Color(0.08, 0.10, 0.18);

        // Materials
        auto mat_red    = std::make_shared<Material>(Color(0.85, 0.15, 0.15), 0.1, 0.7, 0.4, 64.0, 0.1);
        auto mat_mirror = std::make_shared<Material>(Color(0.95, 0.95, 0.95), 0.05, 0.1, 0.9, 128.0, 0.85);
        auto mat_glass  = std::make_shared<Material>(Material::glass(1.5));
        auto mat_floor  = std::make_shared<Material>(Color(0.9, 0.9, 0.9), 0.15, 0.75, 0.2, 32.0, 0.15);

        // Floor Plane
        auto floor = std::make_shared<Plane>(Point3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), mat_floor);
        floor->enable_checkerboard(1.0, Color(0.18, 0.18, 0.22));
        scene.add(floor);

        // Spheres
        scene.add(std::make_shared<Sphere>(Point3( 0.0, 1.0,  0.0), 1.0, mat_mirror));
        scene.add(std::make_shared<Sphere>(Point3(-2.2, 0.8,  0.5), 0.8, mat_red));
        scene.add(std::make_shared<Sphere>(Point3( 2.2, 0.8, -0.2), 0.8, mat_glass));

        // Illumination
        scene.add_light(Light::area_light(Point3(4.0, 7.0, 3.0), 0.6, Color(1.2, 1.2, 1.1), 8));
        scene.add_light(Light::directional_light(Vec3(-0.5, -1.0, -0.3), Color(0.3, 0.35, 0.45)));

        // 2. Camera Configuration
        const int width = 480;
        const int height = 270; // 16:9 aspect ratio
        Point3 look_from(0.0, 2.5, 6.0);
        Point3 look_at(0.0, 0.8, 0.0);
        Vec3 vup(0.0, 1.0, 0.0);
        double vfov = 38.0;
        double aspect_ratio = static_cast<double>(width) / height;

        Camera camera(look_from, look_at, vup, vfov, aspect_ratio, 0.0, 6.0);

        // 3. Render
        Renderer renderer;
        renderer.samples_per_pixel = 1;
        renderer.max_depth = 5;

        std::cout << "Starting render (" << width << "x" << height << ")...\n";
        Image image = renderer.render(scene, camera, width, height);

        std::cout << "Saving output_render.ppm and output_render.bmp...\n";
        image.save_ppm_binary("output_render.ppm");
        image.save_bmp("output_render.bmp");
        std::cout << "Rendering completed successfully!\n";
        return 0;

    } catch (const std::logic_error& e) {
        std::cerr << "\n[Next Step to Implement]: " << e.what() << "\n";
        return 1;
    }
}
