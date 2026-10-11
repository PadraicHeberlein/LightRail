#include "lightrail/camera/camera.hpp"
#include <cmath>
#include <stdexcept>
#include "lightrail/math/constants.hpp"

namespace lightrail {

Camera::Camera(const Point3& look_from,
               const Point3& look_at,
               const Vec3& vup,
               double vfov_degrees,
               double aspect_ratio,
               double defocus_angle,
               double focus_dist)
    : defocus_angle(defocus_angle), focus_dist(focus_dist) {
    // TODO: Implement camera coordinate frame and viewport geometry:
    // 1. origin = look_from
    // 2. Compute viewport height and width at focus_dist based on vfov_degrees
    // 3. Compute orthonormal basis vectors (u, v, w) from look_from, look_at, and vup
    // 4. Calculate viewport horizontal (viewport_u) and vertical (viewport_v) vectors
    // 5. Calculate viewport_upper_left corner
    // 6. Calculate defocus disk radii if defocus_angle > 0
    throw std::logic_error("Not implemented: Camera::Camera()");
}

void Camera::initialize_for_resolution(int width, int height) {
    // TODO: Compute pixel delta vectors and location of pixel (0, 0)
    // pixel_delta_u = viewport_u_ / width
    // pixel_delta_v = viewport_v_ / height
    // pixel00_loc = viewport_upper_left_ + 0.5 * (pixel_delta_u + pixel_delta_v)
    throw std::logic_error("Not implemented: Camera::initialize_for_resolution()");
}

Point3 Camera::sample_defocus_disk() const {
    // TODO: Sample random point on lens defocus disk:
    // Vec3 p = random_in_unit_disk();
    // return origin + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
    throw std::logic_error("Not implemented: Camera::sample_defocus_disk()");
}

Ray Camera::get_ray(double x, double y, bool sample_jitter) const {
    // TODO: Construct and return ray for pixel (x, y):
    // 1. Add sub-pixel jitter if sample_jitter is true: offset_x = random_double(-0.5, 0.5), etc.
    // 2. pixel_sample = pixel00_loc + ((x + offset_x) * pixel_delta_u) + ((y + offset_y) * pixel_delta_v)
    // 3. ray_origin = (defocus_angle <= 0) ? origin : sample_defocus_disk()
    // 4. ray_direction = pixel_sample - ray_origin
    // 5. return Ray(ray_origin, ray_direction)
    throw std::logic_error("Not implemented: Camera::get_ray()");
}

} // namespace lightrail
