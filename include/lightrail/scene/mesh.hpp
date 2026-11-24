/**
 * @file mesh.hpp
 * @brief Polygonal triangle mesh container with a zero-dependency Wavefront `.obj` parser.
 * @see [Wavefront .obj File Format (Wikipedia)](https://en.wikipedia.org/wiki/Wavefront_.obj_file)
 */
#pragma once

#include <memory>
#include <string>
#include <vector>
#include "lightrail/scene/hittable.hpp"
#include "lightrail/scene/triangle.hpp"

namespace lightrail {

/**
 * @brief Triangle Mesh geometry with handwritten Wavefront `.obj` file loader.
 * @see [Polygon Mesh (Wikipedia)](https://en.wikipedia.org/wiki/Polygon_mesh)
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
     * @brief Parses a Wavefront `.obj` ASCII file into triangle primitives.
     *
     * Supports vertex positions (`v x y z`), triangular and convex polygonal faces (`f v1 v2 v3 ...`),
     * and automatic fan-triangulation of @f$ n @f$-gons into @f$ n - 2 @f$ triangles.
     *
     * @param filepath Path to the `.obj` file.
     * @param translation World-space offset applied to all loaded vertices.
     * @param scale Uniform scale factor applied prior to translation.
     * @return `true` if the file was opened and parsed successfully, `false` otherwise.
     * @see [Wavefront .obj File Format (Wikipedia)](https://en.wikipedia.org/wiki/Wavefront_.obj_file)
     * @see [Fan Triangulation (Wikipedia)](https://en.wikipedia.org/wiki/Fan_triangulation)
     */
    bool load_obj(const std::string& filepath, const Point3& translation = Point3::zero(), double scale = 1.0);

    /**
     * @brief Computes closest ray intersection against all triangles in the mesh.
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
