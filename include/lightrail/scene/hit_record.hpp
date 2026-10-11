#pragma once

#include <memory>
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
    bool front_face{true};
    std::shared_ptr<Material> material;

    /**
     * @brief Sets normal vector to always point against incident ray.
     * Sets front_face to true if ray is outside the object, false if inside.
     */
    void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

} // namespace lightrail
