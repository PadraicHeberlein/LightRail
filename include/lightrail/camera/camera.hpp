#pragma once

#include <cmath>
#include "lightrail/math/constants.hpp"
#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

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
           double focus_dist = 10.0)
        : defocus_angle(defocus_angle), focus_dist(focus_dist) {
        origin = look_from;

        // Viewport dimensions at the focus plane
        double theta = deg_to_rad(vfov_degrees);
        double h = std::tan(theta / 2.0);
        double viewport_height = 2.0 * h * focus_dist;
        double viewport_width = aspect_ratio * viewport_height;

        // Camera coordinate frame orthonormal basis (u, v, w)
        w_ = unit_vector(look_from - look_at);
        u_ = unit_vector(cross(vup, w_));
        v_ = cross(w_, u_);

        // Vectors across horizontal and down vertical viewport edges
        Vec3 viewport_u = viewport_width * u_;
        Vec3 viewport_v = -viewport_height * v_;

        // Upper-left corner of viewport positioned at focus_dist
        Point3 viewport_upper_left = origin - (focus_dist * w_) - (viewport_u / 2.0) - (viewport_v / 2.0);

        this->viewport_upper_left_ = viewport_upper_left;
        this->viewport_u_ = viewport_u;
        this->viewport_v_ = viewport_v;

        // Calculate lens disk radius for depth of field
        double defocus_radius = focus_dist * std::tan(deg_to_rad(defocus_angle / 2.0));
        defocus_disk_u = u_ * defocus_radius;
        defocus_disk_v = v_ * defocus_radius;
    }

    void initialize_for_resolution(int width, int height) noexcept {
        pixel_delta_u = viewport_u_ / static_cast<double>(width);
        pixel_delta_v = viewport_v_ / static_cast<double>(height);
        pixel00_loc = viewport_upper_left_ + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    // Generate ray through pixel (x, y) with sub-pixel jitter for anti-aliasing
    // and thin-lens sampling for defocus blur
    Ray get_ray(double x, double y, bool jitter = true) const noexcept {
        double offset_x = jitter ? (random_double() - 0.5) : 0.0;
        double offset_y = jitter ? (random_double() - 0.5) : 0.0;

        Point3 pixel_sample = pixel00_loc + ((x + offset_x) * pixel_delta_u) + ((y + offset_y) * pixel_delta_v);

        Point3 ray_origin = (defocus_angle <= 0.0) ? origin : sample_defocus_disk();
        Vec3 ray_direction = unit_vector(pixel_sample - ray_origin);

        return Ray(ray_origin, ray_direction);
    }

private:
    Point3 sample_defocus_disk() const noexcept {
        Vec3 p = random_in_unit_disk();
        return origin + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
    }

    Vec3 u_, v_, w_;
    Point3 viewport_upper_left_;
    Vec3 viewport_u_;
    Vec3 viewport_v_;
};

} // namespace lightrail
