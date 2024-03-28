#include "Filters/Sharpening.h"

Sharpening::Sharpening() : MatrixFilter({{0, -1, 0}, {-1, MiddleElement, -1}, {0, -1, 0}}){};

std::unique_ptr<Filter> SharpeningMaker::Create(const std::vector<std::string>& args) {
    CheckIfFewArguments("sharp", args, 0);
    return std::make_unique<Sharpening>();
};
