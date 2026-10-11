#pragma once

#include <cmath>
#include <memory>
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

class Sphere : public Hittable {
public:
    Point3 center;
    double radius{1.0};
    std::shared_ptr<Material> material;

    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat)
        : center(center), radius(radius), material(std::move(mat)) {}

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        Vec3 oc = r.origin - center;
        double a = r.direction.length_squared();
        double half_b = dot(oc, r.direction);
        double c = oc.length_squared() - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0.0) {
            return false;
        }

        double sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable [t_min, t_max] range
        double root = (-half_b - sqrtd) / a;
        if (root < t_min || root > t_max) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || root > t_max) {
                return false;
            }
        }

        rec.t = root;
        rec.point = r.at(rec.t);
        Vec3 outward_normal = (rec.point - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.material = material;

        return true;
    }
};

} // namespace lightrail
