#pragma once

#include <memory>
#include <vector>
#include "lightrail/lighting/light.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

class Scene : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;
    std::vector<Light> lights;
    Color ambient_light{0.05, 0.05, 0.08};
    Color background_color{0.05, 0.07, 0.12}; // Subtle dark sky background

    Scene() = default;

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(std::move(object));
    }

    void add_light(const Light& light) {
        lights.push_back(light);
    }

    void clear() noexcept {
        objects.clear();
        lights.clear();
    }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto& object : objects) {
            if (object->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

} // namespace lightrail
