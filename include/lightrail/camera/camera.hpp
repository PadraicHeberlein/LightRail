/**
 * @file camera.hpp
 * @brief Perspective pinhole & thin-lens camera model with sub-pixel SSAA jitter and depth-of-field defocus blur.
 *
 * @image html camera_frustum_dof.svg "Perspective Camera Frustum & Thin-Lens Defocus Blur"
 *
 * @see [Ray Tracing in One Weekend: Positionable Camera](https://raytracing.github.io/books/RayTracingInOneWeekend.html#positionablecamera)
 * @see [Ray Tracing in One Weekend: Defocus Blur](https://raytracing.github.io/books/RayTracingInOneWeekend.html#defocusblur)
 * @see [PBRT v4: Camera Models](https://www.pbr-book.org/4ed/Cameras_and_Film/Camera_Interface)
 */
#pragma once

#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

/**
 * @brief Perspective Camera model supporting vertical field-of-view, look-at orthonormal framing,
 * sub-pixel anti-aliasing jitter, and thin-lens defocus blur (depth of field).
 *
 * Constructs an orthonormal camera basis @f$ (\mathbf{u}, \mathbf{v}, \mathbf{w}) @f$ where
 * @f$ \mathbf{w} = \text{normalize}(\text{look\_from} - \text{look\_at}) @f$,
 * @f$ \mathbf{u} = \text{normalize}(\text{vup} \times \mathbf{w}) @f$, and
 * @f$ \mathbf{v} = \mathbf{w} \times \mathbf{u} @f$.
 *
 * @see [Pinhole Camera Model (Wikipedia)](https://en.wikipedia.org/wiki/Pinhole_camera_model)
 * @see [Depth of Field & Thin Lens Model (Wikipedia)](https://en.wikipedia.org/wiki/Depth_of_field)
 */
class Camera {
public:
    Point3 origin;
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;

    // Defocus blur (depth of field) parameters
    double defocus_angle{0.0};  ///< Variation angle of rays through each pixel in degrees (0 for ideal pinhole).
    double focus_dist{10.0};    ///< Distance from `look_from` to the plane of perfect focus.
    Vec3 defocus_disk_u;        ///< Defocus disk horizontal radius vector.
    Vec3 defocus_disk_v;        ///< Defocus disk vertical radius vector.

    Camera(const Point3& look_from,
           const Point3& look_at,
           const Vec3& vup,
           double vfov_degrees,
           double aspect_ratio,
           double defocus_angle = 0.0,
           double focus_dist = 10.0);

    /**
     * @brief Computes viewport pixel grid deltas (`pixel_delta_u`, `pixel_delta_v`, `pixel00_loc`) for a target resolution.
     * @param width Target image width in pixels.
     * @param height Target image height in pixels.
     */
    void initialize_for_resolution(int width, int height);

    /**
     * @brief Generates a primary ray passing through pixel @f$ (x, y) @f$.
     * @param x Horizontal pixel index.
     * @param y Vertical pixel index.
     * @param sample_jitter When `true`, adds uniform sub-pixel jitter in @f$ [-0.5, 0.5] @f$ for super-sampled anti-aliasing (SSAA).
     * @return Generated primary `Ray` in world space.
     * @see [Supersampling Anti-Aliasing (Wikipedia)](https://en.wikipedia.org/wiki/Supersampling)
     */
    [[nodiscard]] Ray get_ray(double x, double y, bool sample_jitter = false) const;

private:
    Vec3 u_;
    Vec3 v_;
    Vec3 w_;
    Point3 viewport_upper_left_;
    Vec3 viewport_u_;
    Vec3 viewport_v_;

    Point3 sample_defocus_disk() const;
};

} // namespace lightrail
