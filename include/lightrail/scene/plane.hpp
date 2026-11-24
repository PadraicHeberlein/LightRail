/**
 * @file plane.hpp
 * @brief Infinite 3D plane geometry with analytical ray-plane intersection and procedural checkerboard shading.
 * @see [Scratchapixel: Ray-Plane and Ray-Disk Intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html)
 * @see [Line-Plane Intersection (Wikipedia)](https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection)
 */
#pragma once

#include <memory>
#include "lightrail/image/color.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief Infinite 3D Plane geometry defined by @f$ (\mathbf{P} - \mathbf{P}_0) \cdot \mathbf{N} = 0 @f$.
 *
 * Ported from undergrad `PlaneR3.cs` and `LineR3.cs`.
 *
 * @see [Plane (Geometry) (Wikipedia)](https://en.wikipedia.org/wiki/Plane_(geometry))
 */
class Plane : public Hittable {
public:
    Point3 point_on_plane;
    Vec3 normal;
    std::shared_ptr<Material> material;
    double checker_scale{1.0};
    Color checker_color2{0.2, 0.2, 0.2};
    bool checkerboard{false};

    /// @brief Constructs a plane from a point on the plane and a normal vector.
    Plane(const Point3& point, const Vec3& normal, std::shared_ptr<Material> mat);

    /// @brief Constructs a plane passing through three non-collinear points @p p0, @p p1, @p p2.
    Plane(const Point3& p0, const Point3& p1, const Point3& p2, std::shared_ptr<Material> mat);

    /// @brief Enables procedural 2D checkerboard pattern modulation across the plane.
    void enable_checkerboard(double scale = 1.0, const Color& color2 = Color(0.2, 0.2, 0.2));

    /**
     * @brief Tests analytical ray-plane intersection.
     *
     * Substituting @f$ \mathbf{P}(t) = \mathbf{O} + t\mathbf{D} @f$ into
     * @f$ (\mathbf{P} - \mathbf{P}_0) \cdot \mathbf{N} = 0 @f$ yields:
     * @f$ t = \frac{(\mathbf{P}_0 - \mathbf{O}) \cdot \mathbf{N}}{\mathbf{D} \cdot \mathbf{N}} @f$.
     *
     * @param r Incident ray.
     * @param t_min Minimum valid ray parameter.
     * @param t_max Maximum valid ray parameter.
     * @param rec Output hit record.
     * @return `true` if the ray is not parallel to the plane and intersects within @f$ [t_{\min}, t_{\max}] @f$.
     * @see [Scratchapixel: Ray-Plane Intersection](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html)
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
