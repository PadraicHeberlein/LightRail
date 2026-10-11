#pragma once

#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

/**
 * @brief Perspective Camera model supporting field-of-view, look-at targeting,
 * sub-pixel anti-aliasing jitter, and thin-lens defocus blur (depth of field).
 */
class Camera {
public:
    Point3 origin;
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;

    // Defocus blur (depth of field) parameters
    double defocus_angle{0.0};  // Variation angle of rays through each pixel (0 for pinhole)
    double focus_dist{10.0};     // Distance from camera look_from to plane of perfect focus
    Vec3 defocus_disk_u;        // Defocus disk horizontal radius
    Vec3 defocus_disk_v;        // Defocus disk vertical radius

    Camera(const Point3& look_from,
           const Point3& look_at,
           const Vec3& vup,
           double vfov_degrees,
           double aspect_ratio,
           double defocus_angle = 0.0,
           double focus_dist = 10.0);

    /**
     * @brief Computes pixel grid delta vectors given image resolution.
     */
    void initialize_for_resolution(int width, int height);

    /**
     * @brief Generates a ray passing through pixel (x, y).
     * @param x Horizontal pixel index.
     * @param y Vertical pixel index.
     * @param sample_jitter When true, adds uniform sub-pixel jitter in [-0.5, 0.5] for anti-aliasing.
     * @return Generated primary Ray in world space.
     */
    Ray get_ray(double x, double y, bool sample_jitter = false) const;

private:
    Vec3 u_, v_, w_;
    Point3 viewport_upper_left_;
    Vec3 viewport_u_;
    Vec3 viewport_v_;

    Point3 sample_defocus_disk() const;
};

} // namespace lightrail
