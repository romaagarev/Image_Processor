#pragma once
class Pixel {
public:
    Pixel();
    explicit Pixel(float color);
    Pixel(float red, float green, float blue);
    ~Pixel() = default;
    Pixel operator+(const Pixel& another) const;
    Pixel operator-(const Pixel& another) const;
    float operator*(const Pixel& another) const;
    Pixel operator*(const float& parameter) const;
    Pixel operator/(const float& parameter) const;
    Pixel& Normalize();
    float r;
    float g;
    float b;
};

Pixel& operator+=(Pixel& first, const Pixel& second);