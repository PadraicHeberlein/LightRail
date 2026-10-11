#include <cassert>
#include <cmath>
#include <iostream>
#include "lightrail/math/constants.hpp"
#include "lightrail/math/mat3.hpp"
#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"

using namespace lightrail;

void test_vec3() {
    std::cout << "[Test] Vec3 operations... ";

    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);

    // Addition & subtraction
    Vec3 sum = a + b;
    assert(sum.approx_equal(Vec3(5.0, 7.0, 9.0)));

    Vec3 diff = b - a;
    assert(diff.approx_equal(Vec3(3.0, 3.0, 3.0)));

    // Scalar multiplication
    Vec3 scaled = 2.0 * a;
    assert(scaled.approx_equal(Vec3(2.0, 4.0, 6.0)));

    // Dot product
    double d = dot(a, b); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    assert(std::abs(d - 32.0) < kEpsilon);

    // Cross product
    Vec3 c = cross(Vec3::unit_x(), Vec3::unit_y());
    assert(c.approx_equal(Vec3::unit_z()));

    // Parallel & perpendicular checks
    assert(is_parallel(Vec3(1, 2, 3), Vec3(2, 4, 6)));
    assert(is_perpendicular(Vec3(1, 0, 0), Vec3(0, 1, 0)));

    // Reflection (ray hitting a horizontal plane with upward normal)
    Vec3 incident(1.0, -1.0, 0.0);
    Vec3 normal(0.0, 1.0, 0.0);
    Vec3 reflected = reflect(incident, normal);
    assert(reflected.approx_equal(Vec3(1.0, 1.0, 0.0)));

    std::cout << "PASSED\n";
}

void test_ray() {
    std::cout << "[Test] Ray parametric evaluation... ";

    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    Point3 p = r.at(5.0);
    assert(p.approx_equal(Point3(0.0, 0.0, -5.0)));

    std::cout << "PASSED\n";
}

void test_mat3() {
    std::cout << "[Test] Mat3 operations, determinant, and inverse... ";

    Mat3 I = Mat3::identity();
    Vec3 v(3.0, 4.0, 5.0);
    assert((I * v).approx_equal(v));

    Mat3 A(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    // Determinant of A: 1*(0-24) - 2*(0-20) + 3*(0-5) = -24 + 40 - 15 = 1
    double detA = A.determinant();
    assert(std::abs(detA - 1.0) < kEpsilon);

    auto invA = A.inverse();
    assert(invA.has_value());
    Mat3 product = A * (*invA);
    assert(product.row(0).approx_equal(Vec3(1, 0, 0)));
    assert(product.row(1).approx_equal(Vec3(0, 1, 0)));
    assert(product.row(2).approx_equal(Vec3(0, 0, 1)));

    // Test rotation around Z by 90 deg: X axis maps to Y axis
    Mat3 rz = Mat3::rotation_z(kDeg90);
    Vec3 rotated_x = rz * Vec3::unit_x();
    assert(rotated_x.approx_equal(Vec3::unit_y()));

    // Test rotation around Y by 90 deg: Z axis maps to X axis
    Mat3 ry = Mat3::rotation_y(kDeg90);
    Vec3 rotated_z = ry * Vec3::unit_z();
    assert(rotated_z.approx_equal(Vec3::unit_x()));

    std::cout << "PASSED\n";
}

int main() {
    std::cout << "Running LightRail Math Foundation Tests\n";
    std::cout << "======================================\n";
    test_vec3();
    test_ray();
    test_mat3();
    std::cout << "======================================\n";
    std::cout << "All math tests passed successfully!\n";
    return 0;
}
