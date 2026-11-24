/**
 * @file constants.hpp
 * @brief Mathematical constants, angle conversion utilities, and uniform random number helpers.
 * @see [std::numbers (cppreference)](https://en.cppreference.com/w/cpp/numeric/constants)
 * @see [Machine Epsilon (Wikipedia)](https://en.wikipedia.org/wiki/Machine_epsilon)
 */
#pragma once

#include <cmath>
#include <limits>
#include <numbers>

namespace lightrail {

// Mathematical constants
inline constexpr double kPi = std::numbers::pi_v<double>;              ///< Ratio of a circle's circumference to its diameter (@f$ \pi @f$).
inline constexpr double kInfinity = std::numeric_limits<double>::infinity(); ///< Positive IEEE-754 floating-point infinity.
inline constexpr double kEpsilon = std::numeric_limits<double>::epsilon();   ///< Machine epsilon for double precision.

// Common angle constants (in radians)
inline constexpr double kDeg15 = kPi / 12.0;  ///< 15 degrees in radians (@f$ \pi / 12 @f$).
inline constexpr double kDeg30 = kPi / 6.0;   ///< 30 degrees in radians (@f$ \pi / 6 @f$).
inline constexpr double kDeg36 = kPi / 5.0;   ///< 36 degrees in radians (@f$ \pi / 5 @f$).
inline constexpr double kDeg45 = kPi / 4.0;   ///< 45 degrees in radians (@f$ \pi / 4 @f$).
inline constexpr double kDeg60 = kPi / 3.0;   ///< 60 degrees in radians (@f$ \pi / 3 @f$).
inline constexpr double kDeg90 = kPi / 2.0;   ///< 90 degrees in radians (@f$ \pi / 2 @f$).
inline constexpr double kDeg180 = kPi;        ///< 180 degrees in radians (@f$ \pi @f$).

/**
 * @brief Converts an angle from degrees to radians: @f$ \text{rad} = \text{deg} \cdot \frac{\pi}{180} @f$.
 * @param degrees Angle in degrees.
 * @return Equivalent angle in radians.
 * @see [Radian (Wikipedia)](https://en.wikipedia.org/wiki/Radian)
 */
inline constexpr double deg_to_rad(double degrees) noexcept {
    return degrees * kPi / 180.0;
}

/**
 * @brief Converts an angle from radians to degrees: @f$ \text{deg} = \text{rad} \cdot \frac{180}{\pi} @f$.
 * @param radians Angle in radians.
 * @return Equivalent angle in degrees.
 * @see [Radian (Wikipedia)](https://en.wikipedia.org/wiki/Radian)
 */
inline constexpr double rad_to_deg(double radians) noexcept {
    return radians * 180.0 / kPi;
}

/**
 * @brief Generates a pseudo-random real number in @f$ [0.0, 1.0) @f$.
 * @return A uniform random double in @f$ [0.0, 1.0) @f$.
 * @see [Ray Tracing in One Weekend: Random Utilities](https://raytracing.github.io/books/RayTracingInOneWeekend.html#antialiasing/someutilities)
 */
double random_double();

/**
 * @brief Generates a pseudo-random real number in @f$ [\text{min}, \text{max}) @f$.
 * @param min Lower bound (inclusive).
 * @param max Upper bound (exclusive).
 * @return A uniform random double within @f$ [\text{min}, \text{max}) @f$.
 * @see [Continuous Uniform Distribution (Wikipedia)](https://en.wikipedia.org/wiki/Continuous_uniform_distribution)
 */
double random_double(double min, double max);

} // namespace lightrail
