#pragma once

#include "lightrail/image/color.hpp"

namespace lightrail {

// Classic illumination material parameters (Phong / Blinn-Phong model)
struct Material {
    Color albedo{0.8, 0.8, 0.8};
    double ka{0.1};         // Ambient reflection coefficient
    double kd{0.7};         // Diffuse reflection coefficient
    double ks{0.3};         // Specular reflection coefficient
    double shininess{32.0}; // Specular exponent (higher = tighter highlight)
    double reflectivity{0.0}; // 0.0 = matte, 1.0 = perfect mirror reflection

    constexpr Material() noexcept = default;

    constexpr Material(const Color& albedo, double ka, double kd, double ks, double shininess, double reflectivity = 0.0) noexcept
        : albedo(albedo), ka(ka), kd(kd), ks(ks), shininess(shininess), reflectivity(reflectivity) {}

    // Convenience constructors
    static constexpr Material diffuse(const Color& albedo) noexcept {
        return Material(albedo, 0.1, 0.8, 0.1, 16.0, 0.0);
    }

    static constexpr Material glossy(const Color& albedo, double shininess = 64.0) noexcept {
        return Material(albedo, 0.1, 0.6, 0.4, shininess, 0.15);
    }

    static constexpr Material mirror(double reflectivity = 0.85) noexcept {
        return Material(Color(1.0, 1.0, 1.0), 0.05, 0.1, 0.9, 128.0, reflectivity);
    }
};

} // namespace lightrail
