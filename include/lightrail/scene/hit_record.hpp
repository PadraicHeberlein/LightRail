/**
 * @file hit_record.hpp
 * @brief Surface intersection payload recording hit position, oriented normal, ray parameter @f$ t @f$, and material pointer.
 * @see [Ray Tracing in One Weekend: Front Faces Versus Back Faces](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/frontfacesversusbackfaces)
 */
#pragma once

#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

struct Material;

/**
 * @brief Records geometric and material details of a ray-surface intersection point.
 */
struct HitRecord {
    Point3 point;
    Vec3 normal;
    double t{0.0};
    const Material* material{nullptr}; ///< Non-owning observer (owned by Scene geometry).
    bool front_face{true};

    /**
     * @brief Orients `normal` so that it always points against the incident ray @p r.
     *
     * Sets `front_face = dot(r.direction, outward_normal) < 0.0`. If `front_face` is true,
     * the ray struck the outside of the surface; otherwise it originated inside and `normal`
     * is negated.
     *
     * @param r Incident ray.
     * @param outward_normal Geometric outward-pointing unit surface normal.
     * @pre @p outward_normal must be a unit vector.
     * @see [Ray Tracing in One Weekend: Front Faces Versus Back Faces](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/frontfacesversusbackfaces)
     */
    void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

} // namespace lightrail
