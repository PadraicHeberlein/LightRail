#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "lightrail/math/constants.hpp"
#include "lightrail/math/mat3.hpp"
#include "lightrail/math/ray.hpp"
#include "lightrail/math/vec3.hpp"

using namespace lightrail;

#define LIGHTRAIL_CHECK(expr)                                                                         \
    do {                                                                                              \
        if (!(expr)) {                                                                                \
            std::cerr << "CHECK FAILED at " << __FILE__ << ":" << __LINE__ << ": " << #expr << "\n"; \
            std::exit(1);                                                                             \
        }                                                                                             \
    } while (false)

void test_vec3() {
    std::cout << "[Test] Vec3 operations...\n";

    // Constructors, static factories, and exact equality
    constexpr Vec3 z = Vec3::zero();
    LIGHTRAIL_CHECK(z == Vec3(0.0, 0.0, 0.0));
    LIGHTRAIL_CHECK(Vec3::unit_x() == Vec3(1.0, 0.0, 0.0));
    LIGHTRAIL_CHECK(Vec3::unit_y() == Vec3(0.0, 1.0, 0.0));
    LIGHTRAIL_CHECK(Vec3::unit_z() == Vec3(0.0, 0.0, 1.0));
    LIGHTRAIL_CHECK(Vec3::unit_x() != Vec3::unit_y());

    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);

    // Addition, subtraction, and unary negation
    Vec3 sum = a + b;
    LIGHTRAIL_CHECK(sum.approx_equal(Vec3(5.0, 7.0, 9.0)));

    Vec3 diff = b - a;
    LIGHTRAIL_CHECK(diff.approx_equal(Vec3(3.0, 3.0, 3.0)));

    Vec3 neg = -a;
    LIGHTRAIL_CHECK(neg.approx_equal(Vec3(-1.0, -2.0, -3.0)));

    // Scalar multiplication, Hadamard product, and scalar division
    LIGHTRAIL_CHECK((2.0 * a).approx_equal(Vec3(2.0, 4.0, 6.0)));
    LIGHTRAIL_CHECK((a * 2.0).approx_equal(Vec3(2.0, 4.0, 6.0)));
    LIGHTRAIL_CHECK((a * b).approx_equal(Vec3(4.0, 10.0, 18.0)));
    LIGHTRAIL_CHECK((Vec3(2.0, 4.0, 6.0) / 2.0).approx_equal(a));

    // Compound assignments
    Vec3 mut = a;
    mut += b;
    LIGHTRAIL_CHECK(mut.approx_equal(Vec3(5.0, 7.0, 9.0)));
    mut -= b;
    LIGHTRAIL_CHECK(mut.approx_equal(a));
    mut *= 3.0;
    LIGHTRAIL_CHECK(mut.approx_equal(Vec3(3.0, 6.0, 9.0)));
    mut /= 3.0;
    LIGHTRAIL_CHECK(mut.approx_equal(a));

    // Length, length_squared, and unit_vector
    Vec3 v345(3.0, 4.0, 0.0);
    LIGHTRAIL_CHECK(std::abs(v345.length_squared() - 25.0) < kEpsilon);
    LIGHTRAIL_CHECK(std::abs(v345.length() - 5.0) < kEpsilon);
    Vec3 u = unit_vector(v345);
    LIGHTRAIL_CHECK(std::abs(u.length() - 1.0) < kEpsilon);
    LIGHTRAIL_CHECK(u.approx_equal(Vec3(0.6, 0.8, 0.0)));

    // Dot & cross products
    double d = dot(a, b); // 1*4 + 2*5 + 3*6 = 32
    LIGHTRAIL_CHECK(std::abs(d - 32.0) < kEpsilon);

    Vec3 c = cross(Vec3::unit_x(), Vec3::unit_y());
    LIGHTRAIL_CHECK(c.approx_equal(Vec3::unit_z()));
    LIGHTRAIL_CHECK(cross(Vec3::unit_y(), Vec3::unit_x()).approx_equal(-Vec3::unit_z()));
    LIGHTRAIL_CHECK(cross(a, a).approx_equal(Vec3::zero()));

    // Parallel & perpendicular checks (positive, negative, antiparallel, and scale-invariant)
    LIGHTRAIL_CHECK(is_parallel(Vec3(1.0, 2.0, 3.0), Vec3(2.0, 4.0, 6.0)));
    LIGHTRAIL_CHECK(is_parallel(Vec3(1.0, 2.0, 3.0), Vec3(-2.0, -4.0, -6.0)));
    LIGHTRAIL_CHECK(!is_parallel(Vec3::unit_x(), Vec3::unit_y()));
    LIGHTRAIL_CHECK(!is_parallel(Vec3(1e-4, 0.0, 0.0), Vec3(0.0, 1e-4, 0.0)));

    LIGHTRAIL_CHECK(is_perpendicular(Vec3(1.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)));
    LIGHTRAIL_CHECK(is_perpendicular(Vec3(1e5, 0.0, 0.0), Vec3(0.0, 1e5, 0.0)));
    LIGHTRAIL_CHECK(!is_perpendicular(Vec3(1.0, 1.0, 0.0), Vec3(1.0, 0.0, 0.0)));
    LIGHTRAIL_CHECK(!is_perpendicular(Vec3(1e-4, 0.0, 0.0), Vec3(1e-4, 0.0, 0.0)));

    // Reflection (ray hitting a horizontal plane with upward normal)
    Vec3 incident(1.0, -1.0, 0.0);
    Vec3 normal(0.0, 1.0, 0.0);
    Vec3 reflected = reflect(incident, normal);
    LIGHTRAIL_CHECK(reflected.approx_equal(Vec3(1.0, 1.0, 0.0)));

    // Refraction (Snell's Law: normal incidence passes straight through; 45 deg air->glass bends toward normal)
    Vec3 straight_in(0.0, -1.0, 0.0);
    Vec3 straight_out = refract(straight_in, normal, 1.0 / 1.5);
    LIGHTRAIL_CHECK(straight_out.approx_equal(straight_in));

    Vec3 uv = unit_vector(Vec3(1.0, -1.0, 0.0));
    double eta = 1.0 / 1.5;
    Vec3 refracted = refract(uv, normal, eta);
    LIGHTRAIL_CHECK(std::abs(refracted.length() - 1.0) < kEpsilon);
    // sin(theta_out) == eta * sin(theta_in) -> refracted.x == eta * uv.x
    LIGHTRAIL_CHECK(std::abs(refracted.x - eta * uv.x) < kEpsilon);
    LIGHTRAIL_CHECK(refracted.y < 0.0);

    // Linear interpolation
    LIGHTRAIL_CHECK(lerp(a, b, 0.0).approx_equal(a));
    LIGHTRAIL_CHECK(lerp(a, b, 1.0).approx_equal(b));
    LIGHTRAIL_CHECK(lerp(a, b, 0.5).approx_equal(Vec3(2.5, 3.5, 4.5)));

    // Stream formatting
    std::ostringstream oss;
    oss << Vec3(1.0, 2.0, 3.0);
    LIGHTRAIL_CHECK(oss.str() == "(1, 2, 3)");

    std::cout << "  -> Vec3 PASSED\n";
}

void test_ray() {
    std::cout << "[Test] Ray parametric evaluation...\n";

    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    Point3 p = r.at(5.0);
    LIGHTRAIL_CHECK(p.approx_equal(Point3(0.0, 0.0, -5.0)));

    std::cout << "  -> Ray PASSED\n";
}

void test_mat3() {
    std::cout << "[Test] Mat3 operations, determinant, and inverse...\n";

    Mat3 I = Mat3::identity();
    Vec3 v(3.0, 4.0, 5.0);
    LIGHTRAIL_CHECK((I * v).approx_equal(v));

    Mat3 A(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    // Determinant of A: 1*(0-24) - 2*(0-20) + 3*(0-5) = -24 + 40 - 15 = 1
    double detA = A.determinant();
    LIGHTRAIL_CHECK(std::abs(detA - 1.0) < kEpsilon);

    auto invA = A.inverse();
    LIGHTRAIL_CHECK(invA.has_value());
    Mat3 product = A * (*invA);
    LIGHTRAIL_CHECK(product.row(0).approx_equal(Vec3(1, 0, 0)));
    LIGHTRAIL_CHECK(product.row(1).approx_equal(Vec3(0, 1, 0)));
    LIGHTRAIL_CHECK(product.row(2).approx_equal(Vec3(0, 0, 1)));

    // Test rotation around Z by 90 deg: X axis maps to Y axis
    Mat3 rz = Mat3::rotation_z(kDeg90);
    Vec3 rotated_x = rz * Vec3::unit_x();
    LIGHTRAIL_CHECK(rotated_x.approx_equal(Vec3::unit_y()));

    // Test rotation around Y by 90 deg: Z axis maps to X axis
    Mat3 ry = Mat3::rotation_y(kDeg90);
    Vec3 rotated_z = ry * Vec3::unit_z();
    LIGHTRAIL_CHECK(rotated_z.approx_equal(Vec3::unit_x()));

    std::cout << "  -> Mat3 PASSED\n";
}

int main() {
    std::cout << "======================================\n";
    std::cout << "  LightRail Math Foundation Tests     \n";
    std::cout << "======================================\n";
    try {
        test_vec3();
        test_ray();
        test_mat3();
        std::cout << "======================================\n";
        std::cout << "All math tests passed successfully!\n";
        return 0;
    } catch (const std::logic_error& e) {
        std::cerr << "\n[Next Step to Implement]: " << e.what() << "\n";
        return 1;
    }
}
