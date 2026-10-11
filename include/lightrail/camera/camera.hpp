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

    Camera(const Point3& look_from,
           const Point3& look_at,
           const Vec3& vup,
           double vfov_degrees,
           double aspect_ratio) {
        origin = look_from;

        // Viewport dimensions based on vertical field of view
        double theta = deg_to_rad(vfov_degrees);
        double h = std::tan(theta / 2.0);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        // Compute camera coordinate frame orthonormal basis (u, v, w)
        Vec3 w = unit_vector(look_from - look_at);
        Vec3 u = unit_vector(cross(vup, w));
        Vec3 v = cross(w, u);

        // Vectors across horizontal and down vertical viewport edges
        Vec3 viewport_u = viewport_width * u;
        Vec3 viewport_v = -viewport_height * v;

        // Pixel spacing vectors (normalized by image resolution during setup)
        // Upper left corner of viewport at focal length = 1.0 (along -w)
        Point3 viewport_upper_left = origin - w - (viewport_u / 2.0) - (viewport_v / 2.0);

        // Save frame configuration for resolution initialization
        this->viewport_upper_left_ = viewport_upper_left;
        this->viewport_u_ = viewport_u;
        this->viewport_v_ = viewport_v;
    }

    void initialize_for_resolution(int width, int height) noexcept {
        pixel_delta_u = viewport_u_ / static_cast<double>(width);
        pixel_delta_v = viewport_v_ / static_cast<double>(height);
        pixel00_loc = viewport_upper_left_ + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    // Generate ray through pixel (x, y)
    Ray get_ray(double x, double y) const noexcept {
        Point3 pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
        Vec3 ray_direction = unit_vector(pixel_center - origin);
        return Ray(origin, ray_direction);
    }

private:
    Point3 viewport_upper_left_;
    Vec3 viewport_u_;
    Vec3 viewport_v_;
};

} // namespace lightrail
