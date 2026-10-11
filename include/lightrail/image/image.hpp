#pragma once

#include <string>
#include <vector>
#include "lightrail/image/color.hpp"

namespace lightrail {

/**
 * @brief 2D Image pixel buffer with handwritten raw format writers (PPM & BMP).
 */
class Image {
public:
    int width{0};
    int height{0};
    std::vector<Color> pixels;

    Image(int width, int height, Color initial_color = Color::black());

    Color& at(int x, int y);
    const Color& at(int x, int y) const;
    void set(int x, int y, const Color& c);

    /**
     * @brief Writes image to Netpbm PPM binary format (P6).
     * Header format:
     *   P6\n<width> <height>\n255\n
     * Followed by width * height * 3 binary RGB bytes.
     */
    bool save_ppm_binary(const std::string& filepath, bool gamma_correct = true) const;

    /**
     * @brief Writes image to Netpbm PPM ASCII format (P3).
     * Header format:
     *   P3\n<width> <height>\n255\n
     * Followed by space-separated ASCII integers.
     */
    bool save_ppm_ascii(const std::string& filepath, bool gamma_correct = true) const;

    /**
     * @brief Writes image to uncompressed 24-bit Windows Bitmap format (.bmp).
     * Generates BITMAPFILEHEADER (14 bytes) and BITMAPINFOHEADER (40 bytes),
     * writing rows bottom-up in BGR byte order with 4-byte row padding.
     */
    bool save_bmp(const std::string& filepath, bool gamma_correct = true) const;
};

} // namespace lightrail
