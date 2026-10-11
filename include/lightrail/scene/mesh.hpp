#pragma once

#include <memory>
#include <string>
#include <vector>
#include "lightrail/scene/hittable.hpp"
#include "lightrail/scene/triangle.hpp"

namespace lightrail {

/**
 * @brief Triangle Mesh geometry with handwritten Wavefront .obj file loader.
 */
class Mesh : public Hittable {
public:
    std::vector<Triangle> triangles;
    std::shared_ptr<Material> material;

    Mesh() = default;
    explicit Mesh(std::shared_ptr<Material> mat);

    void add_triangle(const Triangle& tri);
    void add_triangle(const Point3& v0, const Point3& v1, const Point3& v2);

    /**
     * @brief Parses a Wavefront .obj ASCII file into triangle primitives.
     * Supports vertices ('v x y z'), triangular & polygonal faces ('f v1 v2 v3...'),
     * and automatic fan-triangulation of n-gons.
     */
    bool load_obj(const std::string& filepath, const Point3& translation = Point3::zero(), double scale = 1.0);

    /**
     * @brief Computes ray intersection testing against all triangles in the mesh.
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
