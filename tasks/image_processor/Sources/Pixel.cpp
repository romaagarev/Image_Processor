#include <algorithm>
#include "Pixel.h"
Pixel::Pixel() : r(0), g(0), b(0){};
Pixel::Pixel(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
}
Pixel::Pixel(float color) : Pixel(color, color, color){};

Pixel Pixel::operator+(const Pixel& another) const {
    return Pixel(r + another.r, g + another.g, b + another.b);
}
Pixel Pixel::operator-(const Pixel& another) const {
    return Pixel(r - another.r, g - another.g, b - another.b);
}
float Pixel::operator*(const Pixel& another) const {
    return r * another.r + g * another.g + b * another.b;
}
Pixel Pixel::operator*(const float& parameter) const {
    return Pixel(r * parameter, g * parameter, b * parameter);
};

Pixel Pixel::operator/(const float& parameter) const {
    return Pixel(r / parameter, g / parameter, b / parameter);
};
Pixel& Pixel::Normalize() {
    if (r > 1) {
        r = 1;
    }
    if (r < 0) {
        r = 0;
    }
    if (g > 1) {
        g = 1;
    }
    if (g < 0) {
        g = 0;
    }
    if (b > 1) {
        b = 1;
    }
    if (b < 0) {
        b = 0;
    }
    return *this;
};

Pixel& operator+=(Pixel& first, const Pixel& second) {
    first = Pixel(first.r + second.r, first.g + second.g, first.b + second.b);
    return first;
}
