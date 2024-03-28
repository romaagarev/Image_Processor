#include "Controller.h"
#include "Filters/Crop.h"
#include "Filters/Grayscale.h"
#include "Filters/Sharpening.h"
#include "Filters/EdgeDetection.h"
#include "Filters/GaussianBlur.h"
#include "Filters/Hexagones.h"

Controller::Controller() {
    makers.insert({"-crop", std::make_unique<CropMaker>()});
    makers.insert({"-gs", std::make_unique<GrayscaleMaker>()});
    makers.insert({"-neg", std::make_unique<NegativeMaker>()});
    makers.insert({"-sharp", std::make_unique<SharpeningMaker>()});
    makers.insert({"-edge", std::make_unique<EdgeDetectionMaker>()});
    makers.insert({"-blur", std::make_unique<GaussianBlurMaker>()});
    makers.insert({"-hex", std::make_unique<HexagonesMaker>()});
}

void Controller::MakeFilterSequence(std::vector<FilterToCreate> makers_sequence) {
    for (const FilterToCreate& maker : makers_sequence) {
        if (makers.find(maker.name) == makers.end()) {
            throw WrongFilterName(maker.name);
        }
        filter_sequence.push_back(makers[maker.name]->Create(maker.args));
    }
}
Image Controller::Apply(const Image& image) const {
    Image result = image;
    for (auto& filter : filter_sequence) {
        result = filter->Apply(result);
    }
    return result;
}