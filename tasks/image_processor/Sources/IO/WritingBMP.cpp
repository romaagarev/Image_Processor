#include "IO/WritingBMP.h"

void SetNumber(unsigned char* begin, const size_t& number) {
    const char first_move = 8;
    const char second_move = 16;
    const char third_move = 24;
    if (IsBigEndian()) {
        ByteSwap(begin);
    }
    begin[0] = number;
    begin[1] = number >> first_move;
    begin[2] = number >> second_move;
    begin[3] = number >> third_move;
}

void WriteBMP::SetNewSizes() {
    padding_amount_ = (4 - (export_image_.GetWidth() * 3) % 4) % 4;
    const size_t file_size = FileHeaderSize + InformationHeaderSize +
                             export_image_.GetWidth() * export_image_.GetHeight() +
                             3 * padding_amount_ * export_image_.GetHeight();
    SetNumber(&(file_header_[FileSizeBeginPosition]), file_size);
    SetNumber(&(information_header_[WidthBeginPosition]), export_image_.GetWidth());
    SetNumber(&(information_header_[HeightBeginPosition]), export_image_.GetHeight());
}

WriteBMP::WriteBMP(Image& image, const ReadBMP& read_bmp) : export_image_(image) {
    for (size_t i = 0; i < FileHeaderSize; i++) {
        file_header_[i] = read_bmp.file_header[i];
    }
    for (size_t j = 0; j < InformationHeaderSize; j++) {
        information_header_[j] = read_bmp.information_header[j];
    }
    SetNewSizes();
}

void WriteBMP::Export(const char* path) {
    std::ofstream f;
    f.open(path, std::ios::binary);
    if (!f.is_open()) {
        throw FileNotOpen(path);
    }
    unsigned char bmp_padding[3] = {0, 0, 0};
    f.write(reinterpret_cast<char*>(file_header_), FileHeaderSize);
    f.write(reinterpret_cast<char*>(information_header_), InformationHeaderSize);
    for (size_t i = export_image_.GetHeight(); i >= 1; i--) {
        for (size_t j = 1; j <= export_image_.GetWidth(); j++) {
            unsigned char r = static_cast<unsigned char>(export_image_(j, i).r * ConvertationConstant);
            unsigned char g = static_cast<unsigned char>(export_image_(j, i).g * ConvertationConstant);
            unsigned char b = static_cast<unsigned char>(export_image_(j, i).b * ConvertationConstant);
            unsigned char pixel[] = {b, g, r};
            f.write(reinterpret_cast<char*>(pixel), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_padding), static_cast<int32_t>(padding_amount_));
    }
    f.close();
}