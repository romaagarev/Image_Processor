#pragma once
#include <exception>
#include <string>

class ExceptionWithParameters : public std::exception {
public:
    const char* what() const noexcept override;
    ExceptionWithParameters(const std::string& incorrect, const std::string& before_parameter,
                            const std::string& after_parameter);
    ~ExceptionWithParameters() override = default;

private:
    std::string message_;
};

class ReadNotBMP : public std::exception {
public:
    const char* what() const noexcept override;
};

class FewArguments : public std::exception {
public:
    const char* what() const noexcept override;
};

class FileNotOpen : public ExceptionWithParameters {
public:
    explicit FileNotOpen(const std::string& incorrect);
    ~FileNotOpen() override = default;
};

class WrongFilterName : public ExceptionWithParameters {
public:
    explicit WrongFilterName(const std::string& incorrect);
    ~WrongFilterName() override = default;
};

class FewFilterArguments : public ExceptionWithParameters {
public:
    explicit FewFilterArguments(const std::string& incorrect);
    ~FewFilterArguments() override = default;
};

class TooBigArguments : public ExceptionWithParameters {
public:
    explicit TooBigArguments(const std::string& incorrect);
    ~TooBigArguments() override = default;
};

class IncorrectArguments : public ExceptionWithParameters {
public:
    explicit IncorrectArguments(const std::string& incorrect);
    ~IncorrectArguments() override = default;
};