#pragma once
#include "Filter.h"

class MatrixFilter : public Filter {
public:
    Image Apply(const Image& image) const override;
    Pixel ApplyMatrix(const Image& image, const int32_t& j, const int32_t& i) const;
    explicit MatrixFilter(std::vector<std::vector<float>> matrix);
    ~MatrixFilter() override = default;

private:
    std::vector<std::vector<float>> matrix_;
    int32_t height_;
    int32_t width_;
    constexpr static const int32_t StartLine = 1;
    constexpr static const int32_t StartColumn = 1;
};
