#pragma once

#include "lightrail/image/color.hpp"
#include "lightrail/math/ray.hpp"
#include "lightrail/scene/hit_record.hpp"

namespace lightrail {

enum class MaterialType {
    Phong,       // Diffuse, Blinn-Phong specular, and mirror reflection
    Dielectric   // Transparent refractive glass/water with Fresnel reflectance
};

/**
 * @brief Surface illumination and scattering material parameters.
 */
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

    // Factory helpers
    static constexpr Material diffuse(const Color& albedo) noexcept {
        return Material(albedo, 0.1, 0.8, 0.1, 16.0, 0.0);
    }

    static constexpr Material glossy(const Color& albedo, double shininess = 64.0) noexcept {
        return Material(albedo, 0.1, 0.6, 0.4, shininess, 0.15);
    }

    static constexpr Material mirror(double reflectivity = 0.85) noexcept {
        return Material(Color(1.0, 1.0, 1.0), 0.05, 0.1, 0.9, 128.0, reflectivity);
    }

    static constexpr Material glass(double index_of_refraction = 1.5, const Color& attenuation = Color(1.0, 1.0, 1.0)) noexcept {
        Material m;
        m.type = MaterialType::Dielectric;
        m.albedo = attenuation;
        m.ior = index_of_refraction;
        return m;
    }

    /**
     * @brief Evaluates ray scattering (reflection or refraction) off material surface.
     * @param r_in Incident ray.
     * @param rec Surface intersection metadata.
     * @param attenuation Color modulation along scattered path.
     * @param scattered Output reflected or refracted ray.
     * @return true if ray scatters, false if absorbed.
     */
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const;

    /**
     * @brief Computes Schlick's polynomial approximation for Fresnel reflectance.
     * Formula: R(theta) = R0 + (1 - R0) * (1 - cos(theta))^5
     * where R0 = ((n1 - n2) / (n1 + n2))^2
     */
    static double reflectance_schlick(double cosine, double ref_idx);
};

} // namespace lightrail
