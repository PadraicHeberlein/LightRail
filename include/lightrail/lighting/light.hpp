#pragma once

#include "lightrail/image/color.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

enum class LightType {
    Point,
    Directional,
    Area // Spherical/Disk area light for soft penumbra shadows
};

/**
 * @brief Illumination light source in 3D world space.
 */
struct Light {
    Point3 position{0.0, 5.0, 0.0};
    Vec3 direction{0.0, -1.0, 0.0};
    Color intensity{1.0, 1.0, 1.0};
    double radius{0.5};
    LightType type{LightType::Point};
    int shadow_samples{8};

    [[nodiscard]] static Light point_light(const Point3& pos, const Color& intensity = Color::white()) noexcept;
    [[nodiscard]] static Light directional_light(const Vec3& dir, const Color& intensity = Color::white()) noexcept;
    [[nodiscard]] static Light area_light(const Point3& pos,
                                          double radius,
                                          const Color& intensity = Color::white(),
                                          int samples = 8) noexcept;

    /**
     * @brief Stochastically samples an emission point on the light source.
     * For Point/Directional lights, returns position.
     * For Area lights, jitters randomly over the sphere/disk radius.
     */
    [[nodiscard]] Point3 sample_point() const;
};

} // namespace lightrail
