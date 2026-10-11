#pragma once

#include <memory>
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief 3D Triangle primitive using the Möller–Trumbore intersection algorithm.
 */
class Triangle : public Hittable {
public:
    Point3 v0, v1, v2;
    Vec3 normal;
    std::shared_ptr<Material> material;

    Triangle(const Point3& v0, const Point3& v1, const Point3& v2, std::shared_ptr<Material> mat);

    /**
     * @brief Computes ray-triangle intersection via Möller–Trumbore algorithm.
     * Evaluates barycentric coordinates (u, v) and ray distance t:
     *   P = (1 - u - v)*v0 + u*v1 + v*v2
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
