#include "Image.h"
#include "iostream"
#include "fstream"
#include "IO/ReadingBMP.h"
#include "Exceptions.h"

void SetNumber(unsigned char* begin, const size_t& number);

class WriteBMP {
private:
    constexpr static const float ConvertationConstant = 255.0f;
    constexpr static const int32_t FileHeaderSize = 14;
    constexpr static const int32_t InformationHeaderSize = 40;
    constexpr static const size_t HeightBeginPosition = 8;
    constexpr static const size_t WidthBeginPosition = 4;
    constexpr static const size_t FileSizeBeginPosition = 2;
    size_t padding_amount_ = 0;
    void SetNewSizes();
    unsigned char file_header_[FileHeaderSize];
    unsigned char information_header_[InformationHeaderSize];
    Image& export_image_;

public:
    WriteBMP(Image& image, const ReadBMP& read_bmp);
    ~WriteBMP() = default;
    void Export(const char* path);
};