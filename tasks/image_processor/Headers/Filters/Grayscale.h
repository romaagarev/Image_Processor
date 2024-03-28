#pragma once
#include "Filters/Filter.h"
#include "Image.h"
#include <memory>
#include <vector>

class Grayscale : public Filter {
public:
    Image Apply(const Image& image) const override;
    Grayscale() = default;
    ~Grayscale() override = default;

private:
    const Pixel constant_ = Pixel(0.299, 0.587, 0.114);
};

class GrayscaleMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    GrayscaleMaker() = default;
    ~GrayscaleMaker() override = default;
};
