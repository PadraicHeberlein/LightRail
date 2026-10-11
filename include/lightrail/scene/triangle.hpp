#pragma once

#include <memory>
#include "lightrail/math/constants.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

// 3D Triangle primitive using the Möller–Trumbore intersection algorithm
class Triangle : public Hittable {
public:
    Point3 v0, v1, v2;
    Vec3 normal;
    std::shared_ptr<Material> material;

    Triangle(const Point3& v0, const Point3& v1, const Point3& v2, std::shared_ptr<Material> mat)
        : v0(v0), v1(v1), v2(v2),
          normal(unit_vector(cross(v1 - v0, v2 - v0))),
          material(std::move(mat)) {}

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        Vec3 edge1 = v1 - v0;
        Vec3 edge2 = v2 - v0;

        Vec3 h = cross(r.direction, edge2);
        double a = dot(edge1, h);

        // Ray is parallel to this triangle
        if (std::abs(a) < kEpsilon) {
            return false;
        }

        double f = 1.0 / a;
        Vec3 s = r.origin - v0;
        double u = f * dot(s, h);

        if (u < 0.0 || u > 1.0) {
            return false;
        }

        Vec3 q = cross(s, edge1);
        double v = f * dot(r.direction, q);

        if (v < 0.0 || (u + v) > 1.0) {
            return false;
        }

        double t = f * dot(edge2, q);

        if (t < t_min || t > t_max) {
            return false;
        }

        rec.t = t;
        rec.point = r.at(t);
        rec.set_face_normal(r, normal);
        rec.material = material;

        return true;
    }
};

} // namespace lightrail
