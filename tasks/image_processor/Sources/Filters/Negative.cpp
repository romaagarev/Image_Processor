#include "Filters/Negative.h"
Image Negative::Apply(const Image& image) const {
    Image result(image.GetWidth(), image.GetHeight());
    for (size_t i = 1; i <= result.GetHeight(); i++) {
        for (size_t j = 1; j <= result.GetWidth(); j++) {
            result(j, i) = Pixel(1, 1, 1) - image(j, i);
        }
    }
    result.MakeLikeNearest();
    return result;
}

std::unique_ptr<Filter> NegativeMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("neg", args, 0);
    return std::make_unique<Negative>();
};
