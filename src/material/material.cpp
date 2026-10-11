#include "lightrail/material/material.hpp"
#include <cmath>
#include <stdexcept>

namespace lightrail {

bool Material::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    // TODO: Implement material scattering logic
    // 1. For Dielectric:
    //    attenuation = albedo;
    //    Determine refraction_ratio = rec.front_face ? (1.0 / ior) : ior;
    //    Compute cos_theta, sin_theta
    //    Check for total internal reflection: cannot_refract = refraction_ratio * sin_theta > 1.0;
    //    Check Schlick's reflectance: reflectance_schlick(cos_theta, refraction_ratio) > random_double()
    //    Choose reflection vs refraction and construct scattered ray
    // 2. For Mirror / Phong reflection:
    //    scattered = Ray(rec.point, reflect(unit_vector(r_in.direction), rec.normal));
    //    attenuation = albedo;
    throw std::logic_error("Not implemented: Material::scatter()");
}

double Material::reflectance_schlick(double cosine, double ref_idx) {
    // TODO: Implement Schlick's approximation for Fresnel reflectance
    // double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    // r0 = r0 * r0;
    // return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
    throw std::logic_error("Not implemented: Material::reflectance_schlick()");
}

} // namespace lightrail
