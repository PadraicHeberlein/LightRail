#include "lightrail/math/constants.hpp"
#include <stdexcept>

namespace lightrail {

double random_double() {
    // TODO: Implement uniform random number generator in [0.0, 1.0)
    // Hint: Consider using thread_local std::mt19937_64 and std::uniform_real_distribution<double>
    throw std::logic_error("Not implemented: random_double()");
}

double random_double(double min, double max) {
    // TODO: Implement uniform random number generator in [min, max)
    // Formula: min + (max - min) * random_double()
    throw std::logic_error("Not implemented: random_double(min, max)");
}

} // namespace lightrail
