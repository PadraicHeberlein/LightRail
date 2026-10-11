#include "lightrail/scene/scene.hpp"
#include <stdexcept>

namespace lightrail {

void Scene::add(std::shared_ptr<Hittable> object) {
    objects.push_back(std::move(object));
}

void Scene::add_light(const Light& light) {
    lights.push_back(light);
}

void Scene::clear() {
    objects.clear();
    lights.clear();
}

bool Scene::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // TODO: Implement aggregate scene hit testing
    // Iterate over all objects in objects:
    // If object->hit(r, t_min, closest_so_far, temp_rec):
    //   hit_anything = true
    //   closest_so_far = temp_rec.t
    //   rec = temp_rec
    throw std::logic_error("Not implemented: Scene::hit()");
}

} // namespace lightrail
