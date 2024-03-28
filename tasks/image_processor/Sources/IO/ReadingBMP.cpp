#include "IO/ReadingBMP.h"

bool IsBigEndian() {
    uint32_t check_number = 0x00000001;
    char* ptr = reinterpret_cast<char*>(&check_number);
    return *ptr != 0x01;
};

void ByteSwap(unsigned char* begin) {
    std::swap(begin[0], begin[3]);
    std::swap(begin[1], begin[2]);
}

size_t GetNumber(unsigned char* begin) {
    size_t number = 0;
    const char first_move = 8;
    const char second_move = 16;
    const char third_move = 24;
    if (IsBigEndian()) {
        ByteSwap(begin);
    }
    number += begin[0];
    number += begin[1] << first_move;
    number += begin[2] << second_move;
    number += begin[3] << third_move;
    return number;
}

void ReadBMP::SetPixel(unsigned char* pixel, Image& image, const size_t& j, const size_t& i) {
    image.SetPixel(
        Pixel(static_cast<float>(pixel[2]) / ConvertationConstant, static_cast<float>(pixel[1]) / ConvertationConstant,
              static_cast<float>(pixel[0]) / ConvertationConstant),
        j, i);
}

Image ReadBMP::Read(const char* path) {
    Image read_image;
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw FileNotOpen(path);
    }
    if (std::filesystem::file_size(path) <= MinimalFileSize) {
        f.close();
        throw ReadNotBMP();
    }
    f.read(reinterpret_cast<char*>(file_header), FileHeaderSize);
    f.read(reinterpret_cast<char*>(information_header), InformationHeaderSize);
    if (file_header[0] != 'B' || file_header[1] != 'M' ||
        information_header[BitsPerPixelInfoBeginPosition] != BitsPerPixel) {
        f.close();
        throw ReadNotBMP();
    }
    read_image.Resize(GetNumber(&(information_header[WidthBeginPosition])),
                      GetNumber(&(information_header[HeightBeginPosition])));
    const int32_t padding_amount = static_cast<int32_t>((4 - (read_image.GetWidth() * 3) % 4) % 4);
    for (size_t i = read_image.GetHeight(); i >= 1; i--) {
        for (size_t j = 1; j <= read_image.GetWidth(); j++) {
            unsigned char pixel[3];
            f.read(reinterpret_cast<char*>(pixel), 3);
            SetPixel(pixel, read_image, j, i);
        }
        f.ignore(padding_amount);
    }
    f.close();
    read_image.MakeLikeNearest();
    return read_image;
}