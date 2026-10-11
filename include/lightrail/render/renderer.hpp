#pragma once

#include "lightrail/camera/camera.hpp"
#include "lightrail/image/color.hpp"
#include "lightrail/image/image.hpp"
#include "lightrail/scene/scene.hpp"

namespace lightrail {

/**
 * @brief Multithreaded Whitted-style Ray Tracer rendering engine.
 */
class Renderer {
public:
    int max_depth{5};         // Maximum recursion depth for reflective/refractive rays
    int samples_per_pixel{1}; // >1 enables anti-aliasing via stochastic super-sampling

    Renderer() = default;

    /**
     * @brief Dispatches scanlines across CPU threads and renders the scene into an Image buffer.
     */
    Image render(const Scene& scene, Camera& camera, int width, int height) const;

    /**
     * @brief Recursively traces a single ray into the scene, accumulating radiance and reflections.
     */
    Color trace_ray(const Ray& ray, const Scene& scene, int depth) const;

    /**
     * @brief Evaluates Blinn-Phong illumination model (ambient + diffuse + specular).
     */
    Color calculate_shading(const Ray& ray, const HitRecord& rec, const Scene& scene, int depth) const;

    /**
     * @brief Casts shadow occlusion rays towards a light source to determine visibility factor in [0.0, 1.0].
     */
    double calculate_shadow_factor(const Point3& hit_point, const Light& light, const Scene& scene) const;
};

} // namespace lightrail
