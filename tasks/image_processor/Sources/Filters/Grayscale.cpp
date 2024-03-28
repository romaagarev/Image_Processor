#include "Filters/Grayscale.h"
Image Grayscale::Apply(const Image& image) const {
    Image result(image.GetWidth(), image.GetHeight());
    for (size_t i = 1; i <= result.GetHeight(); ++i) {
        for (size_t j = 1; j <= result.GetWidth(); ++j) {
            result(j, i) = Pixel(image(j, i) * constant_);
        }
    }
    result.MakeLikeNearest();
    return result;
}

std::unique_ptr<Filter> GrayscaleMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("gs", args, 0);
    return std::make_unique<Grayscale>();
};
