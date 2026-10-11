#pragma once

#include "lightrail/image/color.hpp"

namespace lightrail {

enum class MaterialType {
    Phong,       // Diffuse, Blinn-Phong specular, and mirror reflection
    Dielectric   // Transparent refractive glass/water with Fresnel reflectance
};

// Surface illumination and scattering material
struct Material {
    MaterialType type{MaterialType::Phong};
    Color albedo{0.8, 0.8, 0.8};

    // Phong parameters
    double ka{0.1};           // Ambient coefficient
    double kd{0.7};           // Diffuse coefficient
    double ks{0.3};           // Specular coefficient
    double shininess{32.0};   // Specular exponent
    double reflectivity{0.0}; // Mirror reflection fraction [0.0, 1.0]

    // Dielectric parameters
    double ior{1.5};          // Index of refraction (e.g. 1.0 air, 1.33 water, 1.5 glass, 2.4 diamond)

    constexpr Material() noexcept = default;

    constexpr Material(const Color& albedo, double ka, double kd, double ks, double shininess, double reflectivity = 0.0) noexcept
        : type(MaterialType::Phong), albedo(albedo), ka(ka), kd(kd), ks(ks), shininess(shininess), reflectivity(reflectivity), ior(1.0) {}

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

    // Glass / Dielectric material
    static constexpr Material glass(double index_of_refraction = 1.5, const Color& attenuation = Color(1.0, 1.0, 1.0)) noexcept {
        Material m;
        m.type = MaterialType::Dielectric;
        m.albedo = attenuation;
        m.ior = index_of_refraction;
        return m;
    }

    // Schlick's approximation for Fresnel reflectance
    static double reflectance(double cosine, double ref_idx) noexcept {
        double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
    }
};

} // namespace lightrail
