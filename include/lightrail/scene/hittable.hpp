/**
 * @file hittable.hpp
 * @brief Abstract polymorphic interface for all ray-intersectable 3D scene primitives and aggregates.
 * @see [Ray Tracing in One Weekend: An Abstraction for Hittable Objects](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/anabstractionforhittableobjects)
 */
#pragma once

#include "lightrail/math/ray.hpp"
#include "lightrail/scene/hit_record.hpp"

namespace lightrail {

/**
 * @brief Abstract base class representing any ray-intersectable 3D geometric entity.
 * @see [Ray Tracing in One Weekend: Hittable Objects](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/anabstractionforhittableobjects)
 * @see [PBRT v4: Shapes](https://www.pbr-book.org/4ed/Shapes)
 */
class Hittable {
public:
    virtual ~Hittable() = default;

    /**
     * @brief Computes ray-primitive intersection within the open/closed interval @f$ [t_{\min}, t_{\max}] @f$.
     * @param r The incident ray.
     * @param t_min Minimum valid ray parameter (typically a small positive epsilon to prevent self-intersection / shadow acne).
     * @param t_max Maximum valid ray parameter (tightened to the closest hit distance found so far).
     * @param rec Output intersection record populated if a valid hit occurs.
     * @return `true` if the ray intersects the object within @f$ [t_{\min}, t_{\max}] @f$, `false` otherwise.
     * @see [Ray Tracing in One Weekend: Fixing Shadow Acne](https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials/fixingshadowacne)
     */
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

} // namespace lightrail
