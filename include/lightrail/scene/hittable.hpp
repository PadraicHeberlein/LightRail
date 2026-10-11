#pragma once

#include "lightrail/math/ray.hpp"
#include "lightrail/scene/hit_record.hpp"

namespace lightrail {

/**
 * @brief Abstract base class representing any ray-intersectable 3D geometric entity.
 */
class Hittable {
public:
    virtual ~Hittable() = default;

    /**
     * @brief Computes ray-primitive intersection within interval [t_min, t_max].
     * @param r The incident ray.
     * @param t_min Minimum valid ray parameter (used to prevent self-intersection shadow acne).
     * @param t_max Maximum valid ray parameter.
     * @param rec Output intersection record populated if a hit occurs.
     * @return true if ray intersects object within [t_min, t_max], false otherwise.
     */
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

} // namespace lightrail
