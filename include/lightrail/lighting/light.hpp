#pragma once

#include "lightrail/image/color.hpp"
#include "lightrail/math/constants.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

enum class LightType {
    Point,
    Directional,
    Area // Spherical/Disk area light for realistic soft shadows (penumbra)
};

struct Light {
    LightType type{LightType::Point};
    Point3 position{0.0, 5.0, 0.0};     // Center position
    Vec3 direction{0.0, -1.0, 0.0};     // Direction (for directional lights)
    Color intensity{1.0, 1.0, 1.0};     // Radiance / color
    double radius{0.5};                 // Radius for Area lights
    int shadow_samples{8};              // Number of shadow sample rays for soft penumbra

    static Light point_light(const Point3& pos, const Color& intensity = Color::white()) noexcept {
        Light l;
        l.type = LightType::Point;
        l.position = pos;
        l.intensity = intensity;
        l.shadow_samples = 1;
        return l;
    }

    static Light directional_light(const Vec3& dir, const Color& intensity = Color::white()) noexcept {
        Light l;
        l.type = LightType::Directional;
        l.direction = unit_vector(dir);
        l.intensity = intensity;
        l.shadow_samples = 1;
        return l;
    }

    static Light area_light(const Point3& pos, double radius, const Color& intensity = Color::white(), int samples = 8) noexcept {
        Light l;
        l.type = LightType::Area;
        l.position = pos;
        l.radius = radius;
        l.intensity = intensity;
        l.shadow_samples = samples;
        return l;
    }

    // Sample an illumination emission point on this light's surface
    Point3 sample_point() const noexcept {
        if (type == LightType::Area) {
            Vec3 offset = radius * random_in_unit_sphere();
            return position + offset;
        }
        return position;
    }
};

} // namespace lightrail
