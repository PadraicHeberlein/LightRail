#pragma once

#include <memory>
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief 3D Sphere geometry.
 * Equation: (P - C) . (P - C) = R^2
 */
class Sphere : public Hittable {
public:
    Point3 center;
    double radius{1.0};
    std::shared_ptr<Material> material;

    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);

    /**
     * @brief Tests ray intersection with sphere using quadratic equation.
     * Ray equation: P(t) = O + t*D
     * Substitution gives quadratic: a*t^2 + 2*h*t + c = 0
     * where:
     *   oc = O - C
     *   a = dot(D, D)
     *   h = dot(oc, D)
     *   c = dot(oc, oc) - R^2
     * Discriminant: h^2 - a*c
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
