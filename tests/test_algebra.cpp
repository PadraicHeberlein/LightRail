#include <iostream>
#include <cassert>
#include <concepts>
#include <stdexcept>
#include "lightrail/math/algebra_concepts.hpp"
#include "lightrail/math/algebra_structures.hpp"
#include "lightrail/math/algebra_functions.hpp"
#include "lightrail/math/complex.hpp"
#include "lightrail/math/quaternion.hpp"
#include "lightrail/math/mat3.hpp"

using namespace lightrail;

// =========================================================================
// Compile-time Algebraic Concept Assertions
// =========================================================================

// Complex concept checks
static_assert(Group<Complex>, "Complex must satisfy Group");
static_assert(Ring<Complex>, "Complex must satisfy Ring");
static_assert(DivisionRing<Complex>, "Complex must satisfy DivisionRing");
static_assert(Field<Complex>, "Complex must satisfy Field");
static_assert(VectorSpace<Complex>, "Complex must satisfy VectorSpace");
static_assert(Algebra<Complex>, "Complex must satisfy Algebra");
static_assert(NormedAlgebra<Complex>, "Complex must satisfy NormedAlgebra");
static_assert(std::derived_from<Complex, FieldInterface<Complex>>, "Complex must inherit from FieldInterface");

// Quaternion concept checks
static_assert(Group<Quaternion>, "Quaternion must satisfy Group");
static_assert(Ring<Quaternion>, "Quaternion must satisfy Ring");
static_assert(DivisionRing<Quaternion>, "Quaternion must satisfy DivisionRing");
static_assert(!Field<Quaternion>, "Quaternion multiplication is non-commutative (Division Ring, not Field)");
static_assert(VectorSpace<Quaternion>, "Quaternion must satisfy VectorSpace");
static_assert(Algebra<Quaternion>, "Quaternion must satisfy Algebra");
static_assert(NormedAlgebra<Quaternion>, "Quaternion must satisfy NormedAlgebra");
static_assert(std::derived_from<Quaternion, NormedAlgebraInterface<Quaternion, double>>, "Quaternion must inherit from NormedAlgebraInterface");

// Mat3 concept checks
static_assert(Group<Mat3>, "Mat3 must satisfy Group");
static_assert(Ring<Mat3>, "Mat3 must satisfy Ring");
static_assert(!DivisionRing<Mat3>, "Mat3 is not a DivisionRing");
static_assert(!Field<Mat3>, "Mat3 is not a Field");
static_assert(VectorSpace<Mat3>, "Mat3 must satisfy VectorSpace");
static_assert(Algebra<Mat3>, "Mat3 must satisfy Algebra");
static_assert(NormedAlgebra<Mat3>, "Mat3 must satisfy NormedAlgebra");
static_assert(std::derived_from<Mat3, NormedAlgebraInterface<Mat3, double>>, "Mat3 must inherit from NormedAlgebraInterface");

// =========================================================================
// Runtime Signature & Stub Verification
// =========================================================================

void test_complex_signatures() {
    std::cout << "[Test] Complex signatures and stubs...\n";

    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    assert(c1.real() == 1.0);
    assert(c1.imag() == 2.0);

    Complex z = Complex::zero();
    assert(z.real() == 0.0 && z.imag() == 0.0);

    Complex one = Complex::one();
    assert(one.real() == 1.0 && one.imag() == 0.0);

    bool caught = false;
    try {
        [[maybe_unused]] Complex sum = c1 + c2;
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented Complex::operator+");

    caught = false;
    try {
        [[maybe_unused]] Complex ex = exp(c1);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented exp(Complex)");

    std::cout << "  -> Complex PASSED\n";
}

void test_quaternion_signatures() {
    std::cout << "[Test] Quaternion signatures and stubs...\n";

    Quaternion q1(1.0, 0.0, 0.0, 0.0);
    Quaternion q2(0.0, 1.0, 0.0, 0.0);
    assert(q1.w == 1.0 && q1.x == 0.0);

    Quaternion id = Quaternion::identity();
    assert(id.w == 1.0 && id.x == 0.0 && id.y == 0.0 && id.z == 0.0);

    Quaternion zero = Quaternion::zero();
    assert(zero.w == 0.0 && zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0);

    bool caught = false;
    try {
        [[maybe_unused]] Quaternion prod = q1 * q2;
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented Quaternion::operator*");

    caught = false;
    try {
        [[maybe_unused]] Quaternion ex = exp(q1);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented exp(Quaternion)");

    std::cout << "  -> Quaternion PASSED\n";
}

void test_mat3_algebra_signatures() {
    std::cout << "[Test] Mat3 algebraic extensions...\n";

    Mat3 m_zero(0.0);
    assert(m_zero.m[0][0] == 0.0 && m_zero.m[1][1] == 0.0 && m_zero.m[2][2] == 0.0);

    Mat3 m_one(1.0);
    assert(m_one.m[0][0] == 1.0 && m_one.m[1][1] == 1.0 && m_one.m[2][2] == 1.0);
    assert(m_one.m[0][1] == 0.0 && m_one.m[1][0] == 0.0);

    bool caught = false;
    try {
        [[maybe_unused]] Mat3 neg = -m_one;
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented Mat3::operator-");

    caught = false;
    try {
        [[maybe_unused]] double n = norm(m_one);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented norm(Mat3)");

    std::cout << "  -> Mat3 algebra extensions PASSED\n";
}

void test_algebra_functions_and_optimization_bridges() {
    std::cout << "[Test] Algebra functions and optimization bridges...\n";

    // Test generic identity and zero helpers
    Complex cid = identity_element<Complex>();
    assert(cid.real() == 1.0 && cid.imag() == 0.0);

    Quaternion qid = identity_element<Quaternion>();
    assert(qid.w == 1.0 && qid.x == 0.0);

    Complex cz = zero_element<Complex>();
    assert(cz.real() == 0.0 && cz.imag() == 0.0);

    bool caught = false;
    try {
        [[maybe_unused]] Quaternion q_exp = exp_taylor(qid);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented exp_taylor");

    caught = false;
    try {
        Mat3 a(1.0);
        Mat3 b(1.0);
        [[maybe_unused]] Mat3 opt = optimize_rotation_multiply(a, b);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented optimize_rotation_multiply");

    caught = false;
    try {
        Mat3 omega(0.0);
        [[maybe_unused]] Mat3 r = exp_skew_symmetric(omega);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented exp_skew_symmetric");

    caught = false;
    try {
        Quaternion a = Quaternion::identity();
        Quaternion b = Quaternion::identity();
        [[maybe_unused]] Quaternion res = slerp_algebraic(a, b, 0.5);
    } catch (const std::logic_error& e) {
        caught = true;
    }
    assert(caught && "Expected std::logic_error for unimplemented slerp_algebraic");

    std::cout << "  -> Algebra functions & optimization bridges PASSED\n";
}

int main() {
    std::cout << "======================================\n";
    std::cout << "  LightRail Abstract Algebra Tests    \n";
    std::cout << "======================================\n";

    test_complex_signatures();
    test_quaternion_signatures();
    test_mat3_algebra_signatures();
    test_algebra_functions_and_optimization_bridges();

    std::cout << "======================================\n";
    std::cout << "All abstract algebra tests passed!\n";
    std::cout << "======================================\n";
    return 0;
}
