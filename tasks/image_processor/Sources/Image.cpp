#include "Image.h"

void Image::SetPixel(Pixel pixel, size_t j, size_t i) {
    data[i][j] = pixel;
}

void Image::SetWidth(const size_t& m) {
    for (auto& line : data) {
        line.resize(m + 2, {0, 0, 0});
    }
    width_ = m;
}

void Image::Resize(const size_t& m, const size_t& n) {
    SetHeight(n);
    SetWidth(m);
}

void Image::SetHeight(const size_t& n) {
    data.resize(n + 2);
    height_ = n;
}

size_t Image::GetHeight() const {
    return height_;
}
size_t Image::GetWidth() const {
    return width_;
}

Pixel& Image::operator()(const size_t& j, const size_t& i) {
    return data[i][j];
}
Pixel Image::operator()(const size_t& j, const size_t& i) const {
    return data[i][j];
}

Image::Image(size_t width, size_t height) {
    Resize(width, height);
}

void Image::MakeLikeNearest() {
    data[0][0] = data[1][1];
    data[GetHeight() + 1][0] = data[GetHeight()][1];
    data[GetHeight() + 1][GetWidth() + 1] = data[GetHeight()][GetWidth()];
    data[0][GetWidth() + 1] = data[1][GetWidth()];
    for (size_t i = 1; i <= GetHeight(); i++) {
        data[i][0] = data[i][1];
        data[i][GetWidth() + 1] = data[i][GetWidth()];
    }
    for (size_t j = 1; j <= GetWidth(); j++) {
        data[0][j] = data[1][j];
        data[GetHeight() + 1][j] = data[GetHeight()][j];
    }
}
