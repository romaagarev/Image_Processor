#pragma once
#include <cstdint>
#include "Pixel.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "Image.h"
#include "Exceptions.h"
#include <filesystem>

bool IsBigEndian();

void ByteSwap(unsigned char* begin);

size_t GetNumber(unsigned char* begin);

class ReadBMP {
private:
    constexpr static const float ConvertationConstant = 255.0f;
    constexpr static const int32_t FileHeaderSize = 14;
    constexpr static const int32_t InformationHeaderSize = 40;
    constexpr static const size_t HeightBeginPosition = 8;
    constexpr static const size_t WidthBeginPosition = 4;
    constexpr static const size_t FileSizeBeginPosition = 2;
    constexpr static const size_t BitsPerPixelInfoBeginPosition = 14;
    constexpr static const size_t BitsPerPixel = 24;
    constexpr static const size_t MinimalFileSize = 54;

public:
    unsigned char file_header[FileHeaderSize];
    unsigned char information_header[InformationHeaderSize];
    ~ReadBMP() = default;
    ReadBMP() = default;
    void SetPixel(unsigned char* pixel, Image& image, const size_t& j, const size_t&);
    Image Read(const char* path);
};
