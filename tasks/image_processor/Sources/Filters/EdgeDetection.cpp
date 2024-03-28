#include "Filters/EdgeDetection.h"

Image EdgeDetection::Apply(const Image& image) const {
    Image pre_result = Grayscale().Apply(image);
    Image result = MatrixFilter::Apply(pre_result);
    for (size_t i = 1; i <= result.GetHeight(); ++i) {
        for (size_t j = 1; j <= result.GetWidth(); ++j) {
            if (result(j, i).r > threshold_) {
                result(j, i) = Pixel(1);
            } else {
                result(j, i) = Pixel(0);
            }
        }
    }
    result.MakeLikeNearest();
    return result;
}
EdgeDetection::EdgeDetection(const float& threshold)
    : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), threshold_(threshold){};

std::unique_ptr<Filter> EdgeDetectionMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("edge", args, 1);
    CheckIfIncorrectFloat("edge", args);
    return std::make_unique<EdgeDetection>(std::stof(args[0]));
};