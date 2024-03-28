#pragma once
#include "Filters/Filter.h"
#include "Image.h"
#include <memory>
#include <vector>
#include <cmath>
#include "numbers"

class GaussianBlur : public Filter {
public:
    Image Apply(const Image& image) const override;
    explicit GaussianBlur(const float& sigma);
    ~GaussianBlur() override = default;

private:
    Pixel SummarizeInLine(const int32_t& j, const int32_t& i, const Image& image) const;
    Pixel SummarizeInColumn(const int32_t& j, const int32_t& i, const Image& image) const;
    int32_t range_of_count_;
    float quad_sigma_;
    constexpr static const float Pi = 3.1415926;
    constexpr static const float E = 2.71828;
};

class GaussianBlurMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    GaussianBlurMaker() = default;
    ~GaussianBlurMaker() override = default;
};
