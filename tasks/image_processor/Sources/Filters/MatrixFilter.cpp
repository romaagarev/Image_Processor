#include "Filters/MatrixFilter.h"

MatrixFilter::MatrixFilter(std::vector<std::vector<float>> matrix)
    : matrix_(matrix), height_(static_cast<int32_t>(matrix.size())), width_(static_cast<int32_t>(matrix[0].size())){};

Image MatrixFilter::Apply(const Image &image) const {
    Image result(image.GetWidth(), image.GetHeight());
    for (int32_t i = 1; i <= static_cast<int32_t>(image.GetHeight()); ++i) {
        for (int32_t j = 1; j <= static_cast<int32_t>(image.GetWidth()); ++j) {
            result(j, i) = ApplyMatrix(image, j, i);
        }
    }
    result.MakeLikeNearest();
    return result;
}

Pixel MatrixFilter::ApplyMatrix(const Image &image, const int32_t &j, const int32_t &i) const {
    Pixel result_pixel(0);
    for (int32_t line = 0; line < height_; line++) {
        for (int32_t column = 0; column < width_; column++) {
            size_t diff_line = line - StartLine;
            size_t diff_column = column - StartColumn;
            result_pixel += image(j + diff_column, i + diff_line) * matrix_[line][column];
        }
    }
    return result_pixel.Normalize();
}