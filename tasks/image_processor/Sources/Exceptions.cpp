#include "Exceptions.h"

ExceptionWithParameters::ExceptionWithParameters(const std::string& before_parameter, const std::string& incorrect,
                                                 const std::string& after_parameter)
    : message_(before_parameter + incorrect + after_parameter){};

const char* ExceptionWithParameters::what() const noexcept {
    return message_.c_str();
};

const char* ReadNotBMP::what() const noexcept {
    return "Входной файл не является файлом необходимого типа(24-битный BMP)";
}

const char* FewArguments::what() const noexcept {
    return "Слишком мало аргументов для запуска программы. Проверьте, ввели ли вы имена входного и выходного файлов";
}

FileNotOpen::FileNotOpen(const std::string& incorrect)
    : ExceptionWithParameters("Файл ", incorrect, " не может быть открыт или не существует"){};

WrongFilterName::WrongFilterName(const std::string& incorrect)
    : ExceptionWithParameters("Было введено неверное имя фильтра: ", incorrect, ". Фильтры не были применены"){};

FewFilterArguments::FewFilterArguments(const std::string& incorrect)
    : ExceptionWithParameters("Для фильтра ", incorrect, " было передано неверное количество аргументов"){};

TooBigArguments::TooBigArguments(const std::string& incorrect)
    : ExceptionWithParameters("Для фильтра ", incorrect,
                              " аргументы превысили допустимые значения. Фильтры не были применены"){};

IncorrectArguments::IncorrectArguments(const std::string& incorrect)
    : ExceptionWithParameters("Для фильтра ", incorrect,
                              " были переданы аргументы некорректных типов. Фильтры не были применены"){};
