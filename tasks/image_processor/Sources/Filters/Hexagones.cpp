#include "Filters/Hexagones.h"
Image Hexagones::Apply(const Image& image) const {
    Image result(image.GetWidth(), image.GetHeight());
    for (int32_t i = 1; i <= static_cast<int32_t>(result.GetHeight()) + line_move_; i += line_move_) {
        for (int32_t j = 1; j <= static_cast<int32_t>(result.GetWidth()) + column_move_; j += column_move_) {
            AroundEffect(j, i, image, result);
        }
    }
    for (int32_t i = line_start_position_; i <= static_cast<int32_t>(result.GetHeight()) + line_move_;
         i += line_move_) {
        for (int32_t j = column_start_position_; j <= static_cast<int32_t>(result.GetWidth()) + column_move_;
             j += column_move_) {
            AroundEffect(j, i, image, result);
        }
    }
    result.MakeLikeNearest();
    return result;
};
void Hexagones::AroundEffect(const int32_t& j, const int32_t& i, const Image& image, Image& result) const {
    int32_t left_border = std::max(1, j - horizontal_size_);
    int32_t right_border = std::min(static_cast<int32_t>(image.GetWidth()), j + horizontal_size_);
    int32_t upper_border = std::max(1, i - vertical_size_);
    int32_t bottom_border = std::min(static_cast<int32_t>(image.GetHeight()), i + vertical_size_);
    Pixel pixel_sum = {0, 0, 0};
    int32_t pixel_count = 0;
    for (int32_t line = upper_border; line <= bottom_border; line++) {
        for (int32_t column = left_border; column <= right_border; column++) {
            if (std::abs(line - i) + std::abs(column - j) <= horizontal_size_) {
                pixel_count++;
                pixel_sum += image(column, line);
            }
        }
    }
    for (int32_t line = upper_border; line <= bottom_border; line++) {
        for (int32_t column = left_border; column <= right_border; column++) {
            if (std::abs(line - i) + std::abs(column - j) <= horizontal_size_) {
                result(column, line) = pixel_sum / static_cast<float>(pixel_count);
            }
        }
    }
};
Hexagones::Hexagones(int32_t size) : vertical_size_(2 * (size / 2)), horizontal_size_(3 * (size / 2)) {
    line_start_position_ = vertical_size_ + 1;
    line_move_ = 2 * vertical_size_;
    column_start_position_ = horizontal_size_ + vertical_size_ / 2 + 2;
    column_move_ = 2 * horizontal_size_ + vertical_size_ + 2;
};

std::unique_ptr<Filter> HexagonesMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("hex", args, 1);
    CheckIfIncorrectInt("hex", args);
    return std::make_unique<Hexagones>(std::stoi(args[0]));
};
