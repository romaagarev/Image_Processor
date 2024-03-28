#pragma once
#include "Filters/Filter.h"
#include "Image.h"
#include <memory>
#include <vector>

class Hexagones : public Filter {
public:
    Image Apply(const Image& image) const override;
    explicit Hexagones(int32_t size);
    ~Hexagones() override = default;

private:
    void AroundEffect(const int32_t& j, const int32_t& i, const Image& image, Image& result) const;
    int32_t vertical_size_;
    int32_t horizontal_size_;
    int32_t line_start_position_;
    int32_t line_move_;
    int32_t column_start_position_;
    int32_t column_move_;
};

class HexagonesMaker : public FilterMaker {
public:
    std::unique_ptr<Filter> Create(const std::vector<std::string>& args) override;
    HexagonesMaker() = default;
    ~HexagonesMaker() override = default;
};
