#include "Filters/Crop.h"

Image Crop::Apply(const Image& image) const {
    Image result(new_width_, new_height_);
    for (size_t i = 1; i <= std::min(result.GetHeight(), image.GetHeight()); ++i) {
        for (size_t j = 1; j <= std::min(result.GetWidth(), image.GetWidth()); ++j) {
            result(j, i) = image(j, i);
        }
    }
    result.MakeLikeNearest();
    return result;
}
Crop::Crop(const size_t& new_width, const size_t& new_height) : new_width_(new_width), new_height_(new_height){};

std::unique_ptr<Filter> CropMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("crop", args, 2);
    CheckIfIncorrectInt("crop", args);
    return std::make_unique<Crop>(std::stoi(args[0]), std::stoi(args[1]));
};
