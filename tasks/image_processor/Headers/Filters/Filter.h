#pragma once
#include "Image.h"
#include <memory>
#include <vector>
#include "Exceptions.h"

struct FilterToCreate {
    std::string name;
    std::vector<std::string> args;
};

class Filter {
public:
    virtual Image Apply(const Image& image) const = 0;
    virtual ~Filter() = default;
};

class FilterMaker {
public:
    virtual std::unique_ptr<Filter> Create(const std::vector<std::string>& args) = 0;
    FilterMaker() = default;
    virtual ~FilterMaker() = default;

protected:
    void CheckIfIncorrectInt(const std::string& filter_name, const std::vector<std::string>& args);
    void CheckIfIncorrectFloat(const std::string& filter_name, const std::vector<std::string>& args);
    void CheckIfFewArguments(const std::string& filter_name, const std::vector<std::string>& args,
                             const size_t& correct_size);
};