#pragma once

#include <cmath>
#include <limits>
#include <numbers>
#include <random>

namespace lightrail {

inline constexpr double kEpsilon = 1e-6;
inline constexpr double kInfinity = std::numeric_limits<double>::infinity();
inline constexpr double kPi = std::numbers::pi_v<double>;

constexpr double deg_to_rad(double degrees) noexcept {
    return degrees * (kPi / 180.0);
}

constexpr double rad_to_deg(double radians) noexcept {
    return radians * (180.0 / kPi);
}

// Common angle constants (preserved from undergrad Constants.cs)
inline constexpr double kDeg15 = kPi / 12.0;
inline constexpr double kDeg30 = kPi / 6.0;
inline constexpr double kDeg36 = kPi / 5.0;
inline constexpr double kDeg45 = kPi / 4.0;
inline constexpr double kDeg60 = kPi / 3.0;
inline constexpr double kDeg90 = kPi / 2.0;
inline constexpr double kDeg180 = kPi;

// Thread-safe fast uniform random number generation in [0.0, 1.0)
inline double random_double() noexcept {
    thread_local std::mt19937_64 generator(std::random_device{}());
    thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double random_double(double min, double max) noexcept {
    return min + (max - min) * random_double();
}

} // namespace lightrail
