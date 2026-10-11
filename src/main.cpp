#include <iostream>
#include <memory>
#include "lightrail/camera/camera.hpp"
#include "lightrail/image/color.hpp"
#include "lightrail/material/material.hpp"
#include "lightrail/math/constants.hpp"
#include "lightrail/math/vec3.hpp"
#include "lightrail/render/renderer.hpp"
#include "lightrail/scene/plane.hpp"
#include "lightrail/scene/scene.hpp"
#include "lightrail/scene/sphere.hpp"

using namespace lightrail;

int main() {
    std::cout << "========================================\n";
    std::cout << "  LightRail C++ Ray Tracer Engine       \n";
    std::cout << "========================================\n";

    // 1. Build Scene
    Scene scene;
    scene.ambient_light = Color(0.12, 0.12, 0.15);
    scene.background_color = Color(0.08, 0.10, 0.18);

    // Materials
    auto mat_red_glossy = std::make_shared<Material>(Color(0.85, 0.15, 0.15), 0.1, 0.7, 0.4, 64.0, 0.1);
    auto mat_mirror     = std::make_shared<Material>(Color(0.95, 0.95, 0.95), 0.05, 0.1, 0.9, 128.0, 0.85);
    auto mat_blue_matte = std::make_shared<Material>(Color(0.15, 0.35, 0.85), 0.1, 0.8, 0.2, 16.0, 0.05);
    auto mat_gold       = std::make_shared<Material>(Color(0.90, 0.75, 0.20), 0.1, 0.6, 0.6, 64.0, 0.3);

    // Floor Plane with checkered pattern (analytical plane from PlaneR3)
    auto mat_floor = std::make_shared<Material>(Color(0.9, 0.9, 0.9), 0.15, 0.75, 0.2, 32.0, 0.15);
    auto floor_plane = std::make_shared<Plane>(Point3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), mat_floor);
    floor_plane->enable_checkerboard(1.0, Color(0.18, 0.18, 0.22));
    scene.add(floor_plane);

    // Spheres
    scene.add(std::make_shared<Sphere>(Point3( 0.0, 1.0,  0.0), 1.0, mat_mirror));     // Center reflective sphere
    scene.add(std::make_shared<Sphere>(Point3(-2.2, 0.8,  0.5), 0.8, mat_red_glossy)); // Left red sphere
    scene.add(std::make_shared<Sphere>(Point3( 2.2, 0.8,  0.5), 0.8, mat_blue_matte)); // Right blue sphere
    scene.add(std::make_shared<Sphere>(Point3( 0.0, 0.4,  2.2), 0.4, mat_gold));       // Front gold sphere

    // Light sources
    scene.add_light(Light::point_light(Point3(-4.0, 7.0, 3.0), Color(1.0, 0.95, 0.90)));  // Main key light
    scene.add_light(Light::point_light(Point3( 5.0, 5.0, 4.0), Color(0.4, 0.50, 0.70)));  // Cool fill light

    // 2. Camera Setup
    const int width = 960;
    const int height = 540; // 16:9 aspect ratio
    const double aspect_ratio = static_cast<double>(width) / height;

    Point3 look_from(0.0, 2.5, 5.5);
    Point3 look_at(0.0, 0.8, 0.0);
    Vec3 vup(0.0, 1.0, 0.0);
    double vfov = 45.0; // degrees

    Camera camera(look_from, look_at, vup, vfov, aspect_ratio);

    // 3. Render
    Renderer renderer;
    renderer.max_depth = 5;

    Image image = renderer.render(scene, camera, width, height);

    // 4. Save to disk in raw formats (both binary Netpbm PPM and uncompressed BMP)
    const std::string ppm_path = "output_render.ppm";
    const std::string bmp_path = "output_render.bmp";

    std::cout << "Saving " << ppm_path << "... " << std::flush;
    if (image.save_ppm_binary(ppm_path)) {
        std::cout << "SUCCESS\n";
    }

    std::cout << "Saving " << bmp_path << "... " << std::flush;
    if (image.save_bmp(bmp_path)) {
        std::cout << "SUCCESS\n";
    }

    std::cout << "========================================\n";
    std::cout << "Rendering complete!\n";
    return 0;
}
