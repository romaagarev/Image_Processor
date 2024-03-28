#include "Filters/GaussianBlur.h"
Image GaussianBlur::Apply(const Image& image) const {
    Image pre_result(image.GetWidth(), image.GetHeight());
    Image result(image.GetWidth(), image.GetHeight());
    for (int32_t i = 1; i <= static_cast<int32_t>(result.GetHeight()); ++i) {
        for (int32_t j = 1; j <= static_cast<int32_t>(result.GetWidth()); ++j) {
            pre_result(j, i) = SummarizeInLine(j, i, image);
        }
    }
    for (int32_t i = 1; i <= static_cast<int32_t>(result.GetHeight()); ++i) {
        for (int32_t j = 1; j <= static_cast<int32_t>(result.GetWidth()); ++j) {
            result(j, i) = SummarizeInColumn(j, i, pre_result).Normalize();
        }
    }
    result.MakeLikeNearest();
    return result;
}
GaussianBlur::GaussianBlur(const float& sigma) : range_of_count_(std::ceil(3 * sigma)), quad_sigma_(2 * sigma * sigma) {
}

Pixel GaussianBlur::SummarizeInLine(const int32_t& j, const int32_t& i, const Image& image) const {
    Pixel result(0, 0, 0);
    int32_t left_border = std::max(1, j - range_of_count_);
    int32_t right_border = std::min(static_cast<int32_t>(image.GetWidth()), j + range_of_count_);
    for (int32_t column = left_border; column <= right_border; ++column) {
        float exp = static_cast<float>((column - j) * (column - j)) / quad_sigma_;
        result += image(column, i) / (std::sqrt(Pi * quad_sigma_) * std::pow(E, exp));
    }
    return result;
}
Pixel GaussianBlur::SummarizeInColumn(const int32_t& j, const int32_t& i, const Image& image) const {
    Pixel result(0, 0, 0);
    int32_t upper_border = std::max(1, i - range_of_count_);
    int32_t bottom_border = std::min(static_cast<int32_t>(image.GetHeight()), i + range_of_count_);
    for (int32_t line = upper_border; line <= bottom_border; ++line) {
        float exp = static_cast<float>((line - i) * (line - i)) / quad_sigma_;
        result += image(j, line) / (std::sqrt(Pi * quad_sigma_) * std::pow(E, exp));
    }
    return result;
}

std::unique_ptr<Filter> GaussianBlurMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("blur", args, 1);
    CheckIfIncorrectFloat("blur", args);
    return std::make_unique<GaussianBlur>(std::stof(args[0]));
};
