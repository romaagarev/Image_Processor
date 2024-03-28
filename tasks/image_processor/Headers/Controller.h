#pragma once
#include "Filters/Filter.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include "Exceptions.h"

class Controller : public Filter {
public:
    void MakeFilterSequence(std::vector<FilterToCreate> makers_sequence);
    Image Apply(const Image& image) const override;
    Controller();
    ~Controller() override = default;

protected:
    std::unordered_map<std::string, std::unique_ptr<FilterMaker>> makers{};
    std::vector<std::unique_ptr<Filter>> filter_sequence{};
};
