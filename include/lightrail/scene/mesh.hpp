#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "lightrail/scene/hittable.hpp"
#include "lightrail/scene/triangle.hpp"

namespace lightrail {

// Triangle Mesh container with handwritten Wavefront .obj file loader
class Mesh : public Hittable {
public:
    std::vector<Triangle> triangles;
    std::shared_ptr<Material> material;

    Mesh() = default;
    explicit Mesh(std::shared_ptr<Material> mat) : material(std::move(mat)) {}

    void add_triangle(const Triangle& tri) {
        triangles.push_back(tri);
    }

    void add_triangle(const Point3& v0, const Point3& v1, const Point3& v2) {
        triangles.emplace_back(v0, v1, v2, material);
    }

    // Handwritten, zero-dependency Wavefront .obj parser
    bool load_obj(const std::string& filepath, const Point3& translation = Point3::zero(), double scale = 1.0) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Mesh::load_obj: Failed to open file: " << filepath << '\n';
            return false;
        }

        std::vector<Point3> vertices;
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                double x, y, z;
                if (iss >> x >> y >> z) {
                    vertices.push_back(translation + scale * Vec3(x, y, z));
                }
            } else if (prefix == "f") {
                std::vector<int> face_indices;
                std::string vertex_token;
                while (iss >> vertex_token) {
                    // Extract vertex index before any slash (handles v, v/vt, v/vt/vn, v//vn)
                    std::size_t slash_pos = vertex_token.find('/');
                    std::string idx_str = (slash_pos == std::string::npos) ? vertex_token : vertex_token.substr(0, slash_pos);
                    int idx = std::stoi(idx_str);
                    // OBJ indices are 1-based; negative indices are relative
                    int resolved_idx = (idx > 0) ? (idx - 1) : static_cast<int>(vertices.size()) + idx;
                    face_indices.push_back(resolved_idx);
                }

                // Fan triangulation for polygons (quads, n-gons)
                for (std::size_t i = 1; i + 1 < face_indices.size(); ++i) {
                    int i0 = face_indices[0];
                    int i1 = face_indices[i];
                    int i2 = face_indices[i + 1];

                    if (i0 < static_cast<int>(vertices.size()) &&
                        i1 < static_cast<int>(vertices.size()) &&
                        i2 < static_cast<int>(vertices.size())) {
                        add_triangle(vertices[i0], vertices[i1], vertices[i2]);
                    }
                }
            }
        }

        return !triangles.empty();
    }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto& tri : triangles) {
            if (tri.hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

} // namespace lightrail
