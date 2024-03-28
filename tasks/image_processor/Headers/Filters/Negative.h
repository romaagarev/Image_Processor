#pragma once
#include "Filters/Filter.h"
#include "Image.h"
#include <memory>
#include <vector>

class Negative : public Filter {
public:
    Image Apply(const Image& image) const override;
    Negative() = default;
    ~Negative() override = default;
};

class NegativeMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    NegativeMaker() = default;
    ~NegativeMaker() override = default;
};
