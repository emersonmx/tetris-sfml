#include "MXG/Random.hpp"

#include <ctime>

namespace mxg {

unsigned int Random::getDevice() {
#if defined(_WIN32)
    return time(nullptr);
#else
    std::random_device device;
    return device();
#endif
}

}
