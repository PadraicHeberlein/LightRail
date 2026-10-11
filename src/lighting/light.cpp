#include "lightrail/lighting/light.hpp"
#include <stdexcept>

namespace lightrail {

Light Light::point_light(const Point3& pos, const Color& intensity) noexcept {
    Light l;
    l.type = LightType::Point;
    l.position = pos;
    l.intensity = intensity;
    l.shadow_samples = 1;
    return l;
}

Light Light::directional_light(const Vec3& dir, const Color& intensity) noexcept {
    Light l;
    l.type = LightType::Directional;
    l.direction = unit_vector(dir);
    l.intensity = intensity;
    l.shadow_samples = 1;
    return l;
}

Light Light::area_light(const Point3& pos, double radius, const Color& intensity, int samples) noexcept {
    Light l;
    l.type = LightType::Area;
    l.position = pos;
    l.radius = radius;
    l.intensity = intensity;
    l.shadow_samples = samples;
    return l;
}

Point3 Light::sample_point() const {
    // TODO: Implement light sampling:
    // If type == LightType::Area, return position + radius * random_in_unit_sphere()
    // Otherwise return position
    throw std::logic_error("Not implemented: Light::sample_point()");
}

} // namespace lightrail
