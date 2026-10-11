#pragma once

#include <memory>
#include <vector>
#include "lightrail/lighting/light.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief Scene container storing hittable geometry objects and illumination sources.
 */
class Scene : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;
    std::vector<Light> lights;
    Color ambient_light{0.08, 0.08, 0.10};
    Color background_color{0.05, 0.07, 0.12};

    Scene() = default;

    void add(std::shared_ptr<Hittable> object);
    void add_light(const Light& light);
    void clear();

    /**
     * @brief Evaluates ray intersection against all objects in the scene,
     * recording the closest valid hit within [t_min, t_max].
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
