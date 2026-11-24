/**
 * @file material.hpp
 * @brief Surface shading parameters and optical scattering (Blinn-Phong, mirror reflection, dielectric Snell refraction & Schlick Fresnel).
 *
 * @image html reflection_refraction.svg "Reflection and Snell's Law Refraction at a Dielectric Interface"
 *
 * @see [Ray Tracing in One Weekend: Dielectrics](https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics)
 * @see [Schlick's Approximation (Wikipedia)](https://en.wikipedia.org/wiki/Schlick%27s_approximation)
 */
#pragma once

#include "lightrail/image/color.hpp"
#include "lightrail/math/ray.hpp"
#include "lightrail/scene/hit_record.hpp"

namespace lightrail {

/// @brief Selects the surface scattering model evaluated by `Material`.
enum class MaterialType {
    Phong,       ///< Diffuse, Blinn-Phong specular, and mirror reflection.
    Dielectric   ///< Transparent refractive glass/water with Fresnel reflectance.
};

/**
 * @brief Surface illumination and scattering material parameters.
 *
 * Supports opaque Blinn-Phong/mirror surfaces (`MaterialType::Phong`) and transparent
 * dielectrics governed by Snell's Law and Schlick's Fresnel approximation (`MaterialType::Dielectric`).
 *
 * @see [Blinn–Phong Reflection Model (Wikipedia)](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
 * @see [Refractive Index (Wikipedia)](https://en.wikipedia.org/wiki/Refractive_index)
 */
struct Material {
    MaterialType type{MaterialType::Phong};
    Color albedo{0.8, 0.8, 0.8};

    // Phong parameters
    double ka{0.1};           ///< Ambient reflection coefficient @f$ k_a @f$.
    double kd{0.7};           ///< Diffuse reflection coefficient @f$ k_d @f$.
    double ks{0.3};           ///< Specular reflection coefficient @f$ k_s @f$.
    double shininess{32.0};   ///< Specular highlight exponent @f$ s @f$.
    double reflectivity{0.0}; ///< Mirror reflection fraction in @f$ [0.0, 1.0] @f$.

    // Dielectric parameters
    double ior{1.5};          ///< Index of refraction @f$ \eta @f$ (1.0 air, 1.33 water, 1.5 glass, 2.4 diamond).

    constexpr Material() noexcept = default;
    constexpr Material(const Color& albedo,
                       double ka,
                       double kd,
                       double ks,
                       double shininess,
                       double reflectivity = 0.0) noexcept
        : type(MaterialType::Phong),
          albedo(albedo),
          ka(ka),
          kd(kd),
          ks(ks),
          shininess(shininess),
          reflectivity(reflectivity),
          ior(1.0) {}

    // Factory helpers
    [[nodiscard]] static constexpr Material diffuse(const Color& albedo) noexcept {
        return Material(albedo, 0.1, 0.8, 0.1, 16.0, 0.0);
    }

    [[nodiscard]] static constexpr Material glossy(const Color& albedo, double shininess = 64.0) noexcept {
        return Material(albedo, 0.1, 0.6, 0.4, shininess, 0.15);
    }

    [[nodiscard]] static constexpr Material mirror(double reflectivity = 0.85) noexcept {
        return Material(Color(1.0, 1.0, 1.0), 0.05, 0.1, 0.9, 128.0, reflectivity);
    }

    [[nodiscard]] static constexpr Material glass(double index_of_refraction = 1.5,
                                                  const Color& attenuation = Color(1.0, 1.0, 1.0)) noexcept {
        Material m;
        m.type = MaterialType::Dielectric;
        m.albedo = attenuation;
        m.ior = index_of_refraction;
        return m;
    }

    /**
     * @brief Evaluates ray scattering (reflection or refraction) off a material surface.
     * @param r_in Incident ray.
     * @param rec Surface intersection metadata.
     * @param attenuation Output color modulation along the scattered path.
     * @param scattered Output reflected or refracted ray.
     * @return `true` if the ray scatters, `false` if absorbed.
     * @see [Total Internal Reflection (Wikipedia)](https://en.wikipedia.org/wiki/Total_internal_reflection)
     */
    [[nodiscard]] bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const;

    /**
     * @brief Computes Schlick's polynomial approximation for Fresnel reflectance.
     *
     * Formula: @f$ R(\theta) = R_0 + (1 - R_0)(1 - \cos\theta)^5 @f$,
     * where @f$ R_0 = \left(\frac{1 - \eta}{1 + \eta}\right)^2 @f$.
     *
     * @param cosine Cosine of the angle between the incident ray and surface normal (@f$ \cos\theta @f$).
     * @param ref_idx Relative index of refraction @f$ \eta @f$.
     * @return Fresnel reflectance probability in @f$ [0, 1] @f$.
     * @see [Schlick's Approximation (Wikipedia)](https://en.wikipedia.org/wiki/Schlick%27s_approximation)
     * @see [Ray Tracing in One Weekend: Schlick Approximation](https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics/schlickapproximation)
     */
    [[nodiscard]] static double reflectance_schlick(double cosine, double ref_idx);
};

} // namespace lightrail
