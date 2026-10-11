#pragma once

#include "lightrail/image/color.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

enum class LightType {
    Point,
    Directional
};

struct Light {
    LightType type{LightType::Point};
    Point3 position{0.0, 5.0, 0.0};     // For Point lights
    Vec3 direction{0.0, -1.0, 0.0};     // For Directional lights (pointing towards scene)
    Color intensity{1.0, 1.0, 1.0};     // Light color & strength

    static Light point_light(const Point3& pos, const Color& intensity = Color::white()) noexcept {
        Light l;
        l.type = LightType::Point;
        l.position = pos;
        l.intensity = intensity;
        return l;
    }

    static Light directional_light(const Vec3& dir, const Color& intensity = Color::white()) noexcept {
        Light l;
        l.type = LightType::Directional;
        l.direction = unit_vector(dir);
        l.intensity = intensity;
        return l;
    }
};

} // namespace lightrail
