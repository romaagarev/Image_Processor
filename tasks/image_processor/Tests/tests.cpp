#include "Exceptions.h"
#include "IO/WritingBMP.h"
#include "Filters/Filter.h"
#include "Filters/Crop.h"
#include "Filters/Grayscale.h"
#include "Filters/Sharpening.h"
#include "Filters/EdgeDetection.h"
#include "Filters/GaussianBlur.h"
#include "Filters/Hexagones.h"
#include <vector>

struct TestCase {
    TestCase(const std::string& test_name, const std::string& expected) : test_name(test_name), expected(expected){};
    std::string test_name = 0;
    std::string expected = "0";
    virtual ~TestCase(){};
};

struct SetNumberTestCase : TestCase {
    SetNumberTestCase(const std::string& test_name, const std::string& expected, const size_t& number)
        : TestCase(test_name, expected), number(number){};
    const size_t number = 0;
    ~SetNumberTestCase() override{};
};

struct GetNumberTestCase : TestCase {
    GetNumberTestCase(const std::string& test_name, const std::string& expected, unsigned char* data)
        : TestCase(test_name, expected) {
        for (size_t i = 0; i < 4; ++i) {
            begin[i] = data[i];
        }
    };
    unsigned char begin[4];
    ~GetNumberTestCase() override{};
};

struct IncorrectArgumentsTestCase : TestCase {
    IncorrectArgumentsTestCase(const std::string& test_name, const std::string& expected, FilterMaker& maker,
                               const std::vector<std::string>& args)
        : TestCase(test_name, expected), maker(maker), args(args){};
    FilterMaker& maker;
    const std::vector<std::string> args;
};

std::string ToString(unsigned char* begin) {
    std::string result;
    for (size_t i = 0; i < 4; ++i) {
        result += std::to_string(begin[i]) + ' ';
    }
    return result;
}

class TestFailedException : public ExceptionWithParameters {
public:
    TestFailedException(const size_t& test_number, TestCase& test, const std::string& actual_result)
        : ExceptionWithParameters(std::string("Тест метода(функции) "), test.test_name,
                                  std::string(" номер ") + std::to_string(test_number) +
                                      std::string(" не был пройден. Ожидалось: ") + test.expected +
                                      std::string(" Результат: ") + actual_result){};
    ~TestFailedException() override{};
};

void SetNumberTesting() {
    std::vector<SetNumberTestCase> cases;
    const size_t number1 = 1;
    const size_t number2 = 773;
    const size_t number3 = 12840;
    if (IsBigEndian()) {
        cases.push_back(SetNumberTestCase("SetNumber", "0 0 0 1 ", number1));
        cases.push_back(SetNumberTestCase("SetNumber", "0 0 3 5 ", number2));
        cases.push_back(SetNumberTestCase("SetNumber", "0 0 50 40 ", number3));

    } else {
        cases.push_back(SetNumberTestCase("SetNumber", "1 0 0 0 ", number1));
        cases.push_back(SetNumberTestCase("SetNumber", "5 3 0 0 ", number2));
        cases.push_back(SetNumberTestCase("SetNumber", "40 50 0 0 ", number3));
    }
    unsigned char begin[4];
    for (size_t i = 0; i < cases.size(); i++) {
        SetNumber(begin, cases[i].number);
        if (ToString(begin) != cases[i].expected) {
            throw TestFailedException(i + 1, cases[i], ToString(begin));
        }
    }
}

void GetNumberTesting() {
    std::vector<GetNumberTestCase> cases;
    const unsigned char ten = 10;
    const unsigned char nineteen = 90;
    unsigned char big_endian_data1[4] = {0, 0, 0, 1};
    unsigned char big_endian_data2[4] = {0, 0, 1, 1};
    unsigned char big_endian_data3[4] = {0, 0, ten, nineteen};
    unsigned char little_endian_data1[4] = {1, 0, 0, 0};
    unsigned char little_endian_data2[4] = {1, 1, 0, 0};
    unsigned char little_endian_data3[4] = {nineteen, ten, 0, 0};
    if (IsBigEndian()) {
        cases.push_back(GetNumberTestCase("GetNumber", "1", big_endian_data1));
        cases.push_back(GetNumberTestCase("GetNumber", "257", big_endian_data2));
        cases.push_back(GetNumberTestCase("GetNumber", "2650", big_endian_data3));

    } else {
        cases.push_back(GetNumberTestCase("GetNumber", "1", little_endian_data1));
        cases.push_back(GetNumberTestCase("GetNumber", "257", little_endian_data2));
        cases.push_back(GetNumberTestCase("GetNumber", "2650", little_endian_data3));
    }
    for (size_t i = 0; i < cases.size(); i++) {
        if (std::to_string(GetNumber(cases[i].begin)) != cases[i].expected) {
            throw TestFailedException(i + 1, cases[i], std::to_string(GetNumber(cases[i].begin)));
        }
    }
}

void IncorrectArgumentsTesting() {
    std::vector<IncorrectArgumentsTestCase> cases;
    CropMaker crop_maker;
    HexagonesMaker hexagones_maker;
    GaussianBlurMaker gaussian_blur_maker;
    EdgeDetectionMaker edge_detection_maker;
    NegativeMaker negative_maker;
    SharpeningMaker sharpening_maker;
    GrayscaleMaker grayscale_maker;
    cases.push_back(IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", crop_maker, {"0", "0.5"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", crop_maker, {"qq", "300"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", hexagones_maker, {"0", "0.5"}));
    cases.push_back(IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", hexagones_maker,
                                               {"100000000000000", "200"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", hexagones_maker, {"100", "gg"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", gaussian_blur_maker, {"100"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", gaussian_blur_maker, {"0", "0.5"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", edge_detection_maker, {"300"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", edge_detection_maker, {"qq"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", negative_maker, {"0", "0.5"}));
    cases.push_back(
        IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", gaussian_blur_maker, {"eee"}));
    cases.push_back(IncorrectArgumentsTestCase("IncorrectArguments", "Выброшено исключение", grayscale_maker, {"ee"}));
    for (size_t i = 0; i < cases.size(); ++i) {
        try {
            cases[i].maker.Create(cases[i].args);
            throw TestFailedException(i + 1, cases[i], "Ожидаемое исключение IncorrectArguments не поймано");
        } catch (ExceptionWithParameters& exception) {
            continue;
        } catch (std::exception& exception) {
            throw TestFailedException(i + 1, cases[i], "Ожидаемое исключение IncorrectArguments не поймано");
        }
    }
};

int main() {
    try {
        SetNumberTesting();
        GetNumberTesting();
        IncorrectArgumentsTesting();
        return EXIT_SUCCESS;
    } catch (TestFailedException& exception) {
        std::cout << exception.what() << '\n';
    } catch (std::exception& exception) {
        std::cout << "Неизвкстное исключение" << '\n';
    }
    return EXIT_FAILURE;
};