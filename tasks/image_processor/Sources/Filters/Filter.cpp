#include "Filters/Filter.h"

void FilterMaker::CheckIfFewArguments(const std::string& filter_name, const std::vector<std::string>& args,
                                      const size_t& correct_size) {
    if (args.size() != correct_size) {
        throw FewFilterArguments(filter_name);
    }
}

void FilterMaker::CheckIfIncorrectInt(const std::string& filter_name, const std::vector<std::string>& args) {
    for (auto& argument : args) {
        for (auto& character : argument) {
            if (std::isdigit(character) == 0) {
                throw IncorrectArguments(filter_name);
            }
        }
    }
}

void FilterMaker::CheckIfIncorrectFloat(const std::string& filter_name, const std::vector<std::string>& args) {
    for (auto& argument : args) {
        size_t amount_of_points = 0;
        for (size_t i = 0; i < argument.size(); i++) {
            if (argument[i] == '.') {
                amount_of_points++;
                if (amount_of_points > 1) {
                    throw IncorrectArguments(filter_name);
                }
                continue;
            }
            if (std::isdigit(argument[i]) == 0) {
                throw IncorrectArguments(filter_name);
            }
        }
    }
}
