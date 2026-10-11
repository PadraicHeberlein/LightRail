#include "lightrail/image/image.hpp"
#include <stdexcept>

namespace lightrail {

Image::Image(int width, int height, Color initial_color)
    : width(width), height(height), pixels(static_cast<std::size_t>(width * height), initial_color) {}

Color& Image::at(int x, int y) {
    return pixels[static_cast<std::size_t>(y * width + x)];
}

const Color& Image::at(int x, int y) const {
    return pixels[static_cast<std::size_t>(y * width + x)];
}

void Image::set(int x, int y, const Color& c) {
    pixels[static_cast<std::size_t>(y * width + x)] = c;
}

bool Image::save_ppm_binary(const std::string& filepath, bool gamma_correct) const {
    // TODO: Implement handwritten PPM P6 binary writer
    // 1. Open std::ofstream in std::ios::binary mode
    // 2. Write header: "P6\n" << width << " " << height << "\n255\n"
    // 3. For each pixel, call to_rgb8(gamma_correct) and write binary bytes [R, G, B]
    throw std::logic_error("Not implemented: Image::save_ppm_binary(filepath)");
}

bool Image::save_ppm_ascii(const std::string& filepath, bool gamma_correct) const {
    // TODO: Implement handwritten PPM P3 ASCII writer
    // 1. Open std::ofstream
    // 2. Write header: "P3\n" << width << " " << height << "\n255\n"
    // 3. For each pixel, write "R G B " as ASCII text
    throw std::logic_error("Not implemented: Image::save_ppm_ascii(filepath)");
}

bool Image::save_bmp(const std::string& filepath, bool gamma_correct) const {
    // TODO: Implement handwritten uncompressed 24-bit BMP writer
    // 1. Calculate row padding to 4-byte boundary: (4 - (width * 3) % 4) % 4
    // 2. Populate 14-byte BITMAPFILEHEADER (magic 'BM', fileSize, offset 54)
    // 3. Populate 40-byte BITMAPINFOHEADER (headerSize 40, width, height, planes 1, bpp 24)
    // 4. Write pixels bottom-to-top (row height-1 down to 0) in BGR order with padding bytes
    throw std::logic_error("Not implemented: Image::save_bmp(filepath)");
}

} // namespace lightrail
