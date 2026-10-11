#pragma once

#include <memory>
#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"
#include "lightrail/material/material.hpp"

namespace lightrail {

struct HitRecord {
    Point3 point;
    Vec3 normal;
    double t{0.0};
    bool front_face{true};
    std::shared_ptr<Material> material;

    // Sets surface normal pointing against incident ray
    void set_face_normal(const Ray& r, const Vec3& outward_normal) noexcept {
        front_face = dot(r.direction, outward_normal) < 0.0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

} // namespace lightrail
