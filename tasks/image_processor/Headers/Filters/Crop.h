#pragma once
#include "Filter.h"
#include <memory>
#include <vector>
#include "Exceptions.h"

class Crop : public Filter {
public:
    Image Apply(const Image& image) const override;
    Crop(const size_t& new_width, const size_t& new_height);
    ~Crop() override = default;

private:
    size_t new_width_;
    size_t new_height_;
};

class CropMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    CropMaker() = default;
    ~CropMaker() override = default;
};
