/**
 * @file scene.hpp
 * @brief Aggregate scene container holding Hittable geometry, Light sources, and global illumination defaults.
 * @see [Ray Tracing in One Weekend: A List of Hittable Objects](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/alistofhittableobjects)
 */
#pragma once

#include <memory>
#include <vector>
#include "lightrail/lighting/light.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief Scene container storing hittable geometry objects and illumination sources.
 *
 * Implements the Composite pattern by deriving from `Hittable` so an entire scene can be
 * intersected with a single `hit()` call.
 *
 * @see [Ray Tracing in One Weekend: Hittable List](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/alistofhittableobjects)
 */
class Scene : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;
    std::vector<Light> lights;
    Color ambient_light{0.08, 0.08, 0.10};
    Color background_color{0.05, 0.07, 0.12};

    Scene() = default;

    void add(std::shared_ptr<Hittable> object);
    void add_light(const Light& light);
    void clear();

    /**
     * @brief Evaluates ray intersection against all objects in the scene, recording the closest valid hit within @f$ [t_{\min}, t_{\max}] @f$.
     *
     * Tightens the upper bound `closest_so_far` after each closer intersection so farther hits are rejected.
     *
     * @param r Incident ray.
     * @param t_min Minimum valid ray parameter.
     * @param t_max Maximum valid ray parameter.
     * @param rec Output record for the nearest intersection.
     * @return `true` if any object was hit within @f$ [t_{\min}, t_{\max}] @f$.
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
