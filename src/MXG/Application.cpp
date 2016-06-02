#include "MXG/Application.hpp"

namespace mxg {

int Application::run() {
    create();

    while (running_) {
        tick();
    }

    destroy();
    return errorCode_;
}

void Application::exit() {
    exit(0);
}

void Application::exit(const int errorCode) {
    errorCode_ = errorCode;
    running_ = false;
}

} /* namespace mxg */
