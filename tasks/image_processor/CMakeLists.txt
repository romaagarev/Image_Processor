add_executable(
    image_processor
        ./Sources/image_processor.cpp
        ./Sources/Image.cpp
        ./Sources/Pixel.cpp
        ./Sources/Filters/Negative.cpp
        ./Sources/Filters/Sharpening.cpp
        ./Sources/Filters/EdgeDetection.cpp
        ./Sources/Filters/Grayscale.cpp
        ./Sources/Filters/Crop.cpp
        ./Sources/Filters/Filter.cpp
        ./Sources/IO/WritingBMP.cpp
        ./Sources/IO/ReadingBMP.cpp
        ./Sources/Controller.cpp
        ./Sources/Filters/GaussianBlur.cpp
        ./Sources/Filters/Hexagones.cpp
        ./Sources/Info.cpp
        ./Sources/Exceptions.cpp
        ./Sources/Filters/MatrixFilter.cpp
)

target_include_directories(
        image_processor
        PUBLIC ./Headers
)
enable_testing()

add_executable(
        tests
        Tests/tests.cpp
        ./Sources/Image.cpp
        ./Sources/Pixel.cpp
        ./Sources/Filters/Negative.cpp
        ./Sources/Filters/Sharpening.cpp
        ./Sources/Filters/EdgeDetection.cpp
        ./Sources/Filters/Grayscale.cpp
        ./Sources/Filters/MatrixFilter.cpp
        ./Sources/Filters/Crop.cpp
        ./Sources/Filters/Filter.cpp
        ./Sources/IO/WritingBMP.cpp
        ./Sources/IO/ReadingBMP.cpp
        ./Sources/Controller.cpp
        ./Sources/Filters/GaussianBlur.cpp
        ./Sources/Filters/Hexagones.cpp
        ./Sources/Info.cpp
        ./Sources/Exceptions.cpp
)

target_include_directories(
        tests
        PUBLIC ./Headers
)
add_test(
        NAME tests
        COMMAND tests
)