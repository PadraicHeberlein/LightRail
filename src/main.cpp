#include <iostream>
#include <memory>
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

    // 1. Scene Construction
    Scene scene;
    scene.ambient_light = Color(0.12, 0.12, 0.15);
    scene.background_color = Color(0.08, 0.10, 0.18);

    // Materials
    auto mat_red_glossy = std::make_shared<Material>(Color(0.85, 0.15, 0.15), 0.1, 0.7, 0.4, 64.0, 0.1);
    auto mat_mirror     = std::make_shared<Material>(Color(0.95, 0.95, 0.95), 0.05, 0.1, 0.9, 128.0, 0.85);
    auto mat_glass      = std::make_shared<Material>(Material::glass(1.5)); // Glass sphere
    auto mat_gold       = std::make_shared<Material>(Color(0.90, 0.75, 0.20), 0.1, 0.6, 0.6, 64.0, 0.2);
    auto mat_emerald    = std::make_shared<Material>(Color(0.15, 0.80, 0.35), 0.1, 0.7, 0.5, 48.0, 0.15);

    // Checkered Floor Plane
    auto mat_floor = std::make_shared<Material>(Color(0.9, 0.9, 0.9), 0.15, 0.75, 0.2, 32.0, 0.15);
    auto floor_plane = std::make_shared<Plane>(Point3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), mat_floor);
    floor_plane->enable_checkerboard(1.0, Color(0.18, 0.18, 0.22));
    scene.add(floor_plane);

    // Spheres
    scene.add(std::make_shared<Sphere>(Point3( 0.0, 1.0,  0.0), 1.0, mat_mirror));     // Center mirror sphere
    scene.add(std::make_shared<Sphere>(Point3(-2.2, 0.8,  0.5), 0.8, mat_red_glossy)); // Left red sphere
    scene.add(std::make_shared<Sphere>(Point3( 2.2, 0.8,  0.5), 0.8, mat_glass));      // Right refractive glass sphere
    scene.add(std::make_shared<Sphere>(Point3( 0.0, 0.4,  2.2), 0.4, mat_gold));       // Front gold sphere

    // Triangle Pyramid Mesh (Demonstrating Möller–Trumbore ray-triangle intersection)
    auto pyramid = std::make_shared<Mesh>(mat_emerald);
    Point3 apex(-1.2, 1.1, 2.0);
    Point3 b0(-1.6, 0.0, 1.6);
    Point3 b1(-0.8, 0.0, 1.6);
    Point3 b2(-0.8, 0.0, 2.4);
    Point3 b3(-1.6, 0.0, 2.4);

    pyramid->add_triangle(apex, b0, b1);
    pyramid->add_triangle(apex, b1, b2);
    pyramid->add_triangle(apex, b2, b3);
    pyramid->add_triangle(apex, b3, b0);
    scene.add(pyramid);

    // Illumination: Area Light for soft penumbra shadows + cool fill light
    scene.add_light(Light::area_light(Point3(-4.0, 7.0, 3.0), 0.6, Color(1.0, 0.95, 0.90), 8));
    scene.add_light(Light::point_light(Point3( 5.0, 5.0, 4.0), Color(0.35, 0.45, 0.65)));

    // 2. Camera Setup (with Depth of Field support)
    const int width = 960;
    const int height = 540;
    const double aspect_ratio = static_cast<double>(width) / height;

    Point3 look_from(0.0, 2.5, 5.5);
    Point3 look_at(0.0, 0.8, 0.0);
    Vec3 vup(0.0, 1.0, 0.0);
    double vfov = 45.0;
    double defocus_angle = 0.5; // Slight depth of field blur
    double focus_dist = (look_from - look_at).length(); // Focus on center mirror sphere

    Camera camera(look_from, look_at, vup, vfov, aspect_ratio, defocus_angle, focus_dist);

    // 3. Render with Anti-Aliasing (4 samples per pixel)
    Renderer renderer;
    renderer.max_depth = 6;
    renderer.samples_per_pixel = 4;

    Image image = renderer.render(scene, camera, width, height);

    // 4. Save Renders
    image.save_ppm_binary("output_render.ppm");
    image.save_bmp("output_render.bmp");
    std::cout << "Saved output_render.ppm and output_render.bmp successfully.\n";

    return 0;
}
