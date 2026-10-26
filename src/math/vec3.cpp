#include "lightrail/math/vec3.hpp"
#include <iostream>
#include <stdexcept>

namespace lightrail {

double Vec3::length() const {

}

double Vec3::length_squared() const {
    return x*x + y*y + z*z;
}

bool Vec3::approx_equal(const Vec3& other, double epsilon) const {
    // TODO: Implement floating-point comparison within epsilon tolerance
    throw std::logic_error("Not implemented: Vec3::approx_equal()");
}

Vec3& Vec3::operator+=(const Vec3& other) {
    // TODO: Implement vector in-place addition
    throw std::logic_error("Not implemented: Vec3::operator+=");
}

Vec3& Vec3::operator-=(const Vec3& other) {
    // TODO: Implement vector in-place subtraction
    throw std::logic_error("Not implemented: Vec3::operator-=");
}

Vec3& Vec3::operator*=(double s) {
    // TODO: Implement vector in-place scalar multiplication
    throw std::logic_error("Not implemented: Vec3::operator*=");
}

Vec3& Vec3::operator/=(double s) {
    // TODO: Implement vector in-place scalar division
    throw std::logic_error("Not implemented: Vec3::operator/=");
}

Vec3 Vec3::operator-() const {
    // TODO: Implement vector unary negation (-x, -y, -z)
    throw std::logic_error("Not implemented: Vec3::operator-");
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
    // TODO: Implement vector addition
    throw std::logic_error("Not implemented: operator+(Vec3, Vec3)");
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    // TODO: Implement vector subtraction
    throw std::logic_error("Not implemented: operator-(Vec3, Vec3)");
}

Vec3 operator*(const Vec3& a, const Vec3& b) {
    // TODO: Implement component-wise product (a.x * b.x, a.y * b.y, a.z * b.z)
    throw std::logic_error("Not implemented: operator*(Vec3, Vec3)");
}

Vec3 operator*(double s, const Vec3& v) {
    // TODO: Implement scalar * vector
    throw std::logic_error("Not implemented: operator*(double, Vec3)");
}

Vec3 operator*(const Vec3& v, double s) {
    // TODO: Implement vector * scalar
    throw std::logic_error("Not implemented: operator*(Vec3, double)");
}

Vec3 operator/(const Vec3& v, double s) {
    // TODO: Implement vector / scalar
    throw std::logic_error("Not implemented: operator/(Vec3, double)");
}

double dot(const Vec3& a, const Vec3& b) {
    // TODO: Implement dot product: a.x*b.x + a.y*b.y + a.z*b.z
    throw std::logic_error("Not implemented: dot(Vec3, Vec3)");
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    // TODO: Implement cross product:
    // x = a.y * b.z - a.z * b.y
    // y = a.z * b.x - a.x * b.z
    // z = a.x * b.y - a.y * b.x
    throw std::logic_error("Not implemented: cross(Vec3, Vec3)");
}

Vec3 unit_vector(const Vec3& v) {
    // TODO: Implement unit vector normalization: v / v.length()
    throw std::logic_error("Not implemented: unit_vector(Vec3)");
}

bool is_parallel(const Vec3& a, const Vec3& b) {
    // TODO: Implement parallel vector check (cross product near zero or normalized dot product near +/- 1)
    throw std::logic_error("Not implemented: is_parallel(Vec3, Vec3)");
}

bool is_perpendicular(const Vec3& a, const Vec3& b) {
    // TODO: Implement perpendicular vector check (dot product near zero)
    throw std::logic_error("Not implemented: is_perpendicular(Vec3, Vec3)");
}

Vec3 reflect(const Vec3& v, const Vec3& normal) {
    // TODO: Implement mirror reflection vector:
    // v - 2 * dot(v, normal) * normal
    throw std::logic_error("Not implemented: reflect(Vec3, Vec3)");
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    // TODO: Implement Snell's refraction:
    // double cos_theta = std::min(dot(-uv, n), 1.0);
    // Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    // Vec3 r_out_parallel = -std::sqrt(std::abs(1.0 - r_out_perp.length_squared())) * n;
    // return r_out_perp + r_out_parallel;
    throw std::logic_error("Not implemented: refract(Vec3, Vec3, double)");
}

Vec3 lerp(const Vec3& a, const Vec3& b, double t) {
    // TODO: Implement linear interpolation: (1.0 - t) * a + t * b
    throw std::logic_error("Not implemented: lerp(Vec3, Vec3, double)");
}

Vec3 random_in_unit_sphere() {
    // TODO: Implement rejection sampling for point inside unit sphere
    throw std::logic_error("Not implemented: random_in_unit_sphere()");
}

Vec3 random_unit_vector() {
    // TODO: Implement random unit vector on unit sphere surface: unit_vector(random_in_unit_sphere())
    throw std::logic_error("Not implemented: random_unit_vector()");
}

Vec3 random_in_unit_disk() {
    // TODO: Implement rejection sampling for point inside unit disk (z = 0)
    throw std::logic_error("Not implemented: random_in_unit_disk()");
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

} // namespace lightrail
