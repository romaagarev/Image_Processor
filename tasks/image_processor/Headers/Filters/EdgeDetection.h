#pragma once
#include "MatrixFilter.h"
#include "Image.h"
#include <memory>
#include <vector>
#include "Grayscale.h"
#include "Negative.h"

class EdgeDetection : public MatrixFilter {
public:
    Image Apply(const Image& image) const override;
    explicit EdgeDetection(const float& threshold);
    ~EdgeDetection() override = default;

private:
    float threshold_;
};

class EdgeDetectionMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    EdgeDetectionMaker() = default;
    ~EdgeDetectionMaker() override = default;
};
