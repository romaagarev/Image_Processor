#pragma once
#include <cstdint>
#include "Pixel.h"
#include <vector>
#include <fstream>
#include <functional>

class Image {
public:
    void SetPixel(Pixel pixel, size_t j, size_t i);
    void SetWidth(const size_t& m);
    void SetHeight(const size_t& n);
    void Resize(const size_t& m, const size_t& n);
    size_t GetHeight() const;
    size_t GetWidth() const;
    Pixel& operator()(const size_t& j, const size_t& i);
    Pixel operator()(const size_t& j, const size_t& i) const;
    Image() = default;
    Image(size_t width, size_t height);
    ~Image() = default;
    void MakeLikeNearest();

protected:
    std::vector<std::vector<Pixel>> data;

private:
    size_t height_;
    size_t width_;
};
