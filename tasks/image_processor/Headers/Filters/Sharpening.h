#pragma once
#include "Filters/MatrixFilter.h"
#include "Image.h"
#include <memory>
#include <vector>

class Sharpening : public MatrixFilter {
public:
    Sharpening();
    ~Sharpening() override = default;

private:
    constexpr const static float MiddleElement = 5;
};

class SharpeningMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    SharpeningMaker() = default;
    ~SharpeningMaker() override = default;
};
