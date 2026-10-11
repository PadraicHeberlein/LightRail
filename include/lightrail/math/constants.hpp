#pragma once

#include <cmath>
#include <limits>
#include <numbers>

namespace lightrail {

// Mathematical constants
inline constexpr double kPi = std::numbers::pi_v<double>;
inline constexpr double kInfinity = std::numeric_limits<double>::infinity();
inline constexpr double kEpsilon = 1e-6; // Numerical tolerance for floating-point comparisons

// Common angle constants (in radians)
inline constexpr double kDeg15 = kPi / 12.0;
inline constexpr double kDeg30 = kPi / 6.0;
inline constexpr double kDeg36 = kPi / 5.0;
inline constexpr double kDeg45 = kPi / 4.0;
inline constexpr double kDeg60 = kPi / 3.0;
inline constexpr double kDeg90 = kPi / 2.0;
inline constexpr double kDeg180 = kPi;

// Angle conversions
inline constexpr double deg_to_rad(double degrees) noexcept {
    return degrees * kPi / 180.0;
}

inline constexpr double rad_to_deg(double radians) noexcept {
    return radians * 180.0 / kPi;
}

/**
 * @brief Generates a pseudo-random real number in [0.0, 1.0).
 * @return A uniform random double.
 */
double random_double();

/**
 * @brief Generates a pseudo-random real number in [min, max).
 * @param min Lower bound (inclusive).
 * @param max Upper bound (exclusive).
 * @return A uniform random double within [min, max).
 */
double random_double(double min, double max);

} // namespace lightrail
