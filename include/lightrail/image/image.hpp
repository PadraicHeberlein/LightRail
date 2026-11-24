/**
 * @file image.hpp
 * @brief 2D floating-point framebuffer and zero-dependency Netpbm (`.ppm`) and Windows Bitmap (`.bmp`) writers.
 * @see [Netpbm PPM Format (Wikipedia)](https://en.wikipedia.org/wiki/Netpbm)
 * @see [BMP File Format (Wikipedia)](https://en.wikipedia.org/wiki/BMP_file_format)
 */
#pragma once

#include <string>
#include <vector>
#include "lightrail/image/color.hpp"

namespace lightrail {

/**
 * @brief 2D Image pixel buffer with handwritten raw format writers (PPM & BMP).
 * @see [Ray Tracing in One Weekend: The PPM Image Format](https://raytracing.github.io/books/RayTracingInOneWeekend.html#outputanimage/theppmimageformat)
 */
class Image {
public:
    int width{0};
    int height{0};
    std::vector<Color> pixels;

    Image(int width, int height, Color initial_color = Color::black());

    [[nodiscard]] Color& at(int x, int y);
    [[nodiscard]] const Color& at(int x, int y) const;
    void set(int x, int y, const Color& c);

    /**
     * @brief Writes the image to Netpbm PPM binary format (`P6`).
     *
     * Header format: `P6\n<width> <height>\n255\n`, followed by `width * height * 3` raw RGB bytes.
     *
     * @param filepath Destination file path.
     * @param gamma_correct Whether to apply gamma encoding before 8-bit quantization.
     * @return `true` on write success, `false` on I/O failure.
     * @see [Netpbm PPM Specification](https://netpbm.sourceforge.net/doc/ppm.html)
     */
    [[nodiscard]] bool save_ppm_binary(const std::string& filepath, bool gamma_correct = true) const;

    /**
     * @brief Writes the image to Netpbm PPM ASCII format (`P3`).
     *
     * Header format: `P3\n<width> <height>\n255\n`, followed by space-separated decimal RGB triplets.
     *
     * @param filepath Destination file path.
     * @param gamma_correct Whether to apply gamma encoding before 8-bit quantization.
     * @return `true` on write success, `false` on I/O failure.
     * @see [Netpbm PPM Specification](https://netpbm.sourceforge.net/doc/ppm.html)
     */
    [[nodiscard]] bool save_ppm_ascii(const std::string& filepath, bool gamma_correct = true) const;

    /**
     * @brief Writes the image to uncompressed 24-bit Windows Bitmap format (`.bmp`).
     *
     * Packs a 14-byte `BITMAPFILEHEADER` and 40-byte `BITMAPINFOHEADER`, then writes scanlines
     * bottom-up in little-endian BGR byte order padded to 4-byte row boundaries.
     *
     * @param filepath Destination file path.
     * @param gamma_correct Whether to apply gamma encoding before 8-bit quantization.
     * @return `true` on write success, `false` on I/O failure.
     * @see [BMP File Format Specification (Wikipedia)](https://en.wikipedia.org/wiki/BMP_file_format)
     */
    [[nodiscard]] bool save_bmp(const std::string& filepath, bool gamma_correct = true) const;
};

} // namespace lightrail
