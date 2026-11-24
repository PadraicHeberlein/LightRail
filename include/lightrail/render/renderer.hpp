/**
 * @file renderer.hpp
 * @brief Multithreaded Whitted-style recursive ray tracer with Blinn-Phong shading and stochastic soft shadows.
 *
 * @image html render_pipeline.svg "LightRail Whitted Ray Tracing Pipeline"
 *
 * @see [Ray Tracing (Graphics) & Whitted Ray Tracing (Wikipedia)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
 * @see [Scratchapixel: Whitted Ray Tracing Overview](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted.html)
 */
#pragma once

#include "lightrail/camera/camera.hpp"
#include "lightrail/image/color.hpp"
#include "lightrail/image/image.hpp"
#include "lightrail/scene/scene.hpp"

namespace lightrail {

/**
 * @brief Multithreaded Whitted-style Ray Tracer rendering engine.
 * @see [Whitted (1980) Recursive Ray Tracing (Wikipedia)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Recursive_ray_tracing_algorithm)
 */
class Renderer {
public:
    int max_depth{5};         ///< Maximum recursion depth for reflective/refractive bounce rays.
    int samples_per_pixel{1}; ///< Samples per pixel (>1 enables stochastic super-sampled anti-aliasing).

    Renderer() = default;

    /**
     * @brief Dispatches scanlines across CPU threads (`std::thread`) and renders the scene into an `Image` buffer.
     * @param scene Immutable scene containing geometry and light sources.
     * @param camera Camera initialized for the target resolution.
     * @param width Output image width in pixels.
     * @param height Output image height in pixels.
     * @return Rendered floating-point `Image`.
     */
    Image render(const Scene& scene, Camera& camera, int width, int height) const;

    /**
     * @brief Recursively traces a single ray into the scene, accumulating local illumination, reflections, and refractions.
     * @param ray Ray to trace.
     * @param scene Scene to intersect.
     * @param depth Remaining recursion bounce budget (terminates when `depth <= 0`).
     * @return Estimated linear RGB radiance along @p ray.
     */
    Color trace_ray(const Ray& ray, const Scene& scene, int depth) const;

    /**
     * @brief Evaluates the Blinn-Phong illumination model (ambient + Lambertian diffuse + Blinn halfway specular) plus recursive bounces.
     *
     * @image html blinn_phong_vectors.svg "Blinn-Phong Illumination Vectors (N, L, V, H)"
     *
     * @param ray Incident ray.
     * @param rec Closest surface intersection record.
     * @param scene Scene containing lights and geometry.
     * @param depth Remaining recursion bounce budget.
     * @return Shaded linear RGB color at `rec.point`.
     * @see [Blinn–Phong Reflection Model (Wikipedia)](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
     */
    Color calculate_shading(const Ray& ray, const HitRecord& rec, const Scene& scene, int depth) const;

    /**
     * @brief Casts shadow occlusion rays toward @p light to estimate visibility in @f$ [0.0, 1.0] @f$.
     *
     * For area lights, averages visibility across `light.shadow_samples` stochastic points to render soft penumbrae.
     *
     * @param hit_point Surface point being shaded (biased along normal to avoid shadow acne).
     * @param light Target light source.
     * @param scene Scene geometry acting as shadow occluders.
     * @return Visibility fraction (`0.0` = full umbra shadow, `1.0` = fully illuminated).
     * @see [Shadow Ray & Soft Shadows (Wikipedia)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
     */
    double calculate_shadow_factor(const Point3& hit_point, const Light& light, const Scene& scene) const;
};

} // namespace lightrail
