#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{ 0x4D42 }; // File type always BM which is 0x4D42
    uint32_t file_size{ 0 };      // Size of the file in bytes
    uint16_t reserved1{ 0 };      // Reserved, always 0
    uint16_t reserved2{ 0 };      // Reserved, always 0
    uint32_t offset_data{ 0 };    // Start position of pixel data
};

struct BMPInfoHeader {
    uint32_t size{ 0 };           // Size of this header
    int32_t width{ 0 };           // Width of the image
    int32_t height{ 0 };          // Height of the image
    uint16_t planes{ 1 };         // Number of color planes
    uint16_t bit_count{ 24 };      // Number of bits per pixel
    uint32_t compression{ 0 };    // Compression type
    uint32_t size_image{ 0 };     // Size of the image data
    int32_t x_pixels_per_meter{ 0 }; // Pixels per meter in x
    int32_t y_pixels_per_meter{ 0 }; // Pixels per meter in y
    uint32_t colors_used{ 0 };        // Number of colors used
    uint32_t colors_important{ 0 };   // Important colors
};
#pragma pack(pop)

std::vector<std::vector<double>> BmpReader(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Could not open file " << filename << std::endl;
        return {};
    }

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.file_type != 0x4D42) {
        std::cerr << "This is not a valid BMP file." << std::endl;
        return {};
    }

    if (info_header.bit_count != 24) {
        std::cerr << info_header.bit_count<< std::endl << "This BMP file is not a 24-bit image." << std::endl;
        return {};
    }

    file.seekg(file_header.offset_data, std::ios::beg);

    const int width = info_header.width;
    const int height = info_header.height;

    std::vector<std::vector<double>> img(height, std::vector<double>(width));

    // Rows in BMP files are padded to multiples of 4 bytes
    int row_padded = (width * 3 + 3) & (~3);
    auto* buffer = new double[row_padded];

    for (int i = 0; i < height; ++i) {
        file.read(reinterpret_cast<char*>(buffer), row_padded);
        for (int j = 0; j < width; ++j) {
            int index = j * 3;
            double blue = buffer[index];
            double green = buffer[index + 1];
            double red = buffer[index + 2];

            img[height - 1 - i][j] = static_cast<double>(0.21 * red + 0.72 * green + 0.07 * blue);
        }
    }

    delete[] buffer;
    return img;
}
