#include "Controller.h"
#include "IO/ReadingBMP.h"
#include "IO/WritingBMP.h"
#include "Info.h"

std::vector<FilterToCreate> SplitArgv(const int& argc, const char** line) {
    const char** ptr_begin = line + std::min(3, argc);
    const char** ptr_end = line + argc;
    std::vector<FilterToCreate> result{};
    while (ptr_begin != ptr_end) {
        if ((*ptr_begin)[0] == '-') {
            result.push_back(FilterToCreate{*ptr_begin++, {}});
        } else {
            result.back().args.push_back(*ptr_begin++);
        }
    }
    return result;
};

int main(int argc, const char** argv) {
    try {
        if (argc == 1) {
            throw Info();
        }
        if (argc < 3) {
            throw FewArguments();
        }
        const char* name_file_in = argv[1];
        const char* name_file_out = argv[2];
        ReadBMP reader;
        Image image = reader.Read(name_file_in);
        Controller c;
        c.MakeFilterSequence(SplitArgv(argc, argv));
        Image result = c.Apply(image);
        WriteBMP writer(result, reader);
        writer.Export(name_file_out);
    } catch (std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
    return 0;
}
