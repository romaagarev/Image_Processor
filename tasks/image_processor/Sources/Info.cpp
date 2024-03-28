#include "Info.h"
#include <iostream>

const char* Info::what() const noexcept {
    return information_;
}
