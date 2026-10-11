#pragma once

#include "lightrail/math/ray.hpp"
#include "lightrail/scene/hit_record.hpp"

namespace lightrail {

class Hittable {
public:
    virtual ~Hittable() = default;

    // Returns true if ray intersects shape within [t_min, t_max] interval
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

} // namespace lightrail
