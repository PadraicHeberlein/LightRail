/**
 * @file triangle.hpp
 * @brief 3D triangle primitive implementing the fast Möller–Trumbore ray-triangle intersection algorithm.
 *
 * @image html moller_trumbore.svg "Möller-Trumbore Ray-Triangle Intersection & Barycentric Coordinates"
 *
 * @see [Möller–Trumbore Intersection Algorithm (Wikipedia)](https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm)
 * @see [Scratchapixel: Ray-Triangle Intersection (Möller-Trumbore)](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html)
 */
#pragma once

#include <memory>
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief 3D Triangle primitive using the Möller–Trumbore intersection algorithm.
 * @see [Barycentric Coordinate System (Wikipedia)](https://en.wikipedia.org/wiki/Barycentric_coordinate_system)
 */
class Triangle : public Hittable {
public:
    Point3 v0;
    Point3 v1;
    Point3 v2;
    Vec3 normal;
    std::shared_ptr<Material> material;

    Triangle(const Point3& v0, const Point3& v1, const Point3& v2, std::shared_ptr<Material> mat);

    /**
     * @brief Computes ray-triangle intersection via the Möller–Trumbore algorithm.
     *
     * Solves @f$ \mathbf{O} + t\mathbf{D} = (1 - u - v)\mathbf{v}_0 + u\mathbf{v}_1 + v\mathbf{v}_2 @f$
     * directly via Cramer's rule without precomputing the triangle's plane equation, accepting hits where
     * @f$ u \ge 0 @f$, @f$ v \ge 0 @f$, and @f$ u + v \le 1 @f$.
     *
     * @param r Incident ray.
     * @param t_min Minimum valid ray parameter.
     * @param t_max Maximum valid ray parameter.
     * @param rec Output hit record.
     * @return `true` if the ray intersects the triangle interior within @f$ [t_{\min}, t_{\max}] @f$.
     * @see [Möller–Trumbore Intersection Algorithm (Wikipedia)](https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm)
     * @see [PBRT v4: Triangle Meshes](https://www.pbr-book.org/4ed/Shapes/Triangle_Meshes)
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
