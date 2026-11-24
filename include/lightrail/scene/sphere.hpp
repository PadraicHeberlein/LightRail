/**
 * @file sphere.hpp
 * @brief Analytical 3D sphere primitive using the reduced quadratic ray-sphere intersection equation.
 *
 * @image html ray_sphere_intersection.svg "Analytical Ray-Sphere Intersection"
 *
 * @see [Ray Tracing in One Weekend: Adding a Sphere](https://raytracing.github.io/books/RayTracingInOneWeekend.html#addingasphere)
 * @see [Scratchapixel: Ray-Sphere Intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html)
 */
#pragma once

#include <memory>
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief 3D Sphere geometry defined by @f$ (\mathbf{P} - \mathbf{C}) \cdot (\mathbf{P} - \mathbf{C}) = R^2 @f$.
 * @see [Line-Sphere Intersection (Wikipedia)](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection)
 */
class Sphere : public Hittable {
public:
    Point3 center;
    double radius{1.0};
    std::shared_ptr<Material> material;

    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);

    /**
     * @brief Tests ray intersection with the sphere using the reduced quadratic formula.
     *
     * Substituting @f$ \mathbf{P}(t) = \mathbf{O} + t\mathbf{D} @f$ into
     * @f$ \|\mathbf{P}(t) - \mathbf{C}\|^2 = R^2 @f$ produces:
     * @f$ a t^2 + 2 h t + c = 0 @f$, where
     * @f$ \mathbf{oc} = \mathbf{O} - \mathbf{C} @f$,
     * @f$ a = \mathbf{D} \cdot \mathbf{D} @f$,
     * @f$ h = \mathbf{oc} \cdot \mathbf{D} @f$, and
     * @f$ c = \mathbf{oc} \cdot \mathbf{oc} - R^2 @f$,
     * with reduced discriminant @f$ \Delta = h^2 - ac @f$.
     *
     * @param r Incident ray.
     * @param t_min Minimum valid ray parameter.
     * @param t_max Maximum valid ray parameter.
     * @param rec Output hit record.
     * @return `true` if the nearest valid root lies in @f$ [t_{\min}, t_{\max}] @f$.
     * @see [Ray Tracing in One Weekend: Simplifying the Ray-Sphere Intersection Code](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/simplifyingtheray-sphereintersectioncode)
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
