#include "lightrail/scene/mesh.hpp"
#include <stdexcept>

namespace lightrail {

Mesh::Mesh(std::shared_ptr<Material> mat) : material(std::move(mat)) {}

void Mesh::add_triangle(const Triangle& tri) {
    triangles.push_back(tri);
}

void Mesh::add_triangle(const Point3& v0, const Point3& v1, const Point3& v2) {
    triangles.emplace_back(v0, v1, v2, material);
}

bool Mesh::load_obj(const std::string& filepath, const Point3& translation, double scale) {
    // TODO: Implement handwritten zero-dependency Wavefront .obj parser
    // 1. Open std::ifstream(filepath)
    // 2. Read line by line with std::getline
    // 3. For 'v x y z': parse vertex and apply translation + scale * v
    // 4. For 'f v1 v2 v3...': parse vertex indices (handling 1-based indexing and negative offsets)
    // 5. Fan-triangulate polygonal faces into triangles (v[0], v[i], v[i+1])
    // 6. Append to triangles container
    throw std::logic_error("Not implemented: Mesh::load_obj(filepath)");
}

bool Mesh::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // TODO: Implement aggregate ray-triangle hit testing
    // Iterate over all triangles, keeping track of closest intersection (closest_so_far = rec.t)
    throw std::logic_error("Not implemented: Mesh::hit()");
}

} // namespace lightrail
