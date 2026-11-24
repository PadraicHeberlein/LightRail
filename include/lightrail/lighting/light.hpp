/**
 * @file light.hpp
 * @brief Point, directional, and spherical/disk area light sources supporting stochastic soft-shadow penumbrae.
 * @see [PBRT v4: Light Sources](https://www.pbr-book.org/4ed/Light_Sources)
 * @see [Scratchapixel: Introduction to Shading (Lights & Shadows)](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-lights.html)
 */
#pragma once

#include "lightrail/image/color.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

/// @brief Classifies the geometric emission model of a `Light`.
enum class LightType {
    Point,       ///< Infinitesimal omnidirectional emitter producing crisp hard shadows.
    Directional, ///< Infinitely distant parallel emitter (e.g. sunlight).
    Area         ///< Finite-radius spherical/disk emitter producing soft penumbra shadows via Monte Carlo sampling.
};

/**
 * @brief Illumination light source in 3D world space.
 * @see [Umbra, Penumbra and Antumbra (Wikipedia)](https://en.wikipedia.org/wiki/Umbra,_penumbra_and_antumbra)
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
     *
     * For `Point` and `Directional` lights, returns `position`.
     * For `Area` lights, jitters uniformly over the emitter radius to integrate soft penumbra visibility.
     *
     * @return Sampled 3D emission point in world space.
     * @see [Distributed Ray Tracing (Cook et al. / Wikipedia)](https://en.wikipedia.org/wiki/Distributed_ray_tracing)
     */
    [[nodiscard]] Point3 sample_point() const;
};

} // namespace lightrail
