#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "lightrail/image/color.hpp"

namespace lightrail {

class Image {
public:
    int width{0};
    int height{0};
    std::vector<Color> pixels;

    Image(int width, int height, Color initial_color = Color::black())
        : width(width), height(height), pixels(static_cast<std::size_t>(width * height), initial_color) {}

    Color& at(int x, int y) noexcept {
        return pixels[static_cast<std::size_t>(y * width + x)];
    }

    const Color& at(int x, int y) const noexcept {
        return pixels[static_cast<std::size_t>(y * width + x)];
    }

    void set(int x, int y, const Color& c) noexcept {
        pixels[static_cast<std::size_t>(y * width + x)] = c;
    }

    // Write image to Netpbm PPM (P6 binary format)
    bool save_ppm_binary(const std::string& filepath, bool gamma_correct = true) const {
        std::ofstream out(filepath, std::ios::binary);
        if (!out) {
            std::cerr << "Error: Could not open file for writing: " << filepath << '\n';
            return false;
        }

        // PPM P6 header: "P6\n<width> <height>\n255\n"
        out << "P6\n" << width << " " << height << "\n255\n";

        std::vector<uint8_t> buffer;
        buffer.reserve(static_cast<std::size_t>(width * height * 3));

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                auto [r, g, b] = at(x, y).to_rgb8(gamma_correct);
                buffer.push_back(r);
                buffer.push_back(g);
                buffer.push_back(b);
            }
        }

        out.write(reinterpret_cast<const char*>(buffer.data()), static_cast<std::streamsize>(buffer.size()));
        return out.good();
    }

    // Write image to Netpbm PPM (P3 ASCII format, human-readable)
    bool save_ppm_ascii(const std::string& filepath, bool gamma_correct = true) const {
        std::ofstream out(filepath);
        if (!out) {
            std::cerr << "Error: Could not open file for writing: " << filepath << '\n';
            return false;
        }

        out << "P3\n" << width << " " << height << "\n255\n";

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                auto [r, g, b] = at(x, y).to_rgb8(gamma_correct);
                out << static_cast<int>(r) << ' '
                    << static_cast<int>(g) << ' '
                    << static_cast<int>(b) << '\n';
            }
        }
        return out.good();
    }

    // Write image to standard uncompressed 24-bit BMP file
    // Zero dependencies: constructs headers and writes padded BGR bytes by hand
    bool save_bmp(const std::string& filepath, bool gamma_correct = true) const {
        std::ofstream out(filepath, std::ios::binary);
        if (!out) {
            std::cerr << "Error: Could not open file for writing: " << filepath << '\n';
            return false;
        }

        // Row size must be padded to a multiple of 4 bytes
        const int bytes_per_pixel = 3; // B, G, R
        const int row_size = ((width * bytes_per_pixel + 3) / 4) * 4;
        const int padding_size = row_size - (width * bytes_per_pixel);
        const uint32_t image_size = static_cast<uint32_t>(row_size * height);
        const uint32_t file_header_size = 14;
        const uint32_t info_header_size = 40;
        const uint32_t total_header_size = file_header_size + info_header_size;
        const uint32_t file_size = total_header_size + image_size;

        // 14-byte BITMAPFILEHEADER
        uint8_t file_header[14] = {
            'B', 'M',                                             // bfType
            static_cast<uint8_t>(file_size),                      // bfSize
            static_cast<uint8_t>(file_size >> 8),
            static_cast<uint8_t>(file_size >> 16),
            static_cast<uint8_t>(file_size >> 24),
            0, 0,                                                 // bfReserved1
            0, 0,                                                 // bfReserved2
            static_cast<uint8_t>(total_header_size),              // bfOffBits
            static_cast<uint8_t>(total_header_size >> 8),
            static_cast<uint8_t>(total_header_size >> 16),
            static_cast<uint8_t>(total_header_size >> 24)
        };

        // 40-byte BITMAPINFOHEADER
        uint8_t info_header[40] = {
            static_cast<uint8_t>(info_header_size),               // biSize
            static_cast<uint8_t>(info_header_size >> 8),
            static_cast<uint8_t>(info_header_size >> 16),
            static_cast<uint8_t>(info_header_size >> 24),
            static_cast<uint8_t>(width),                          // biWidth
            static_cast<uint8_t>(width >> 8),
            static_cast<uint8_t>(width >> 16),
            static_cast<uint8_t>(width >> 24),
            static_cast<uint8_t>(height),                         // biHeight (bottom-to-top)
            static_cast<uint8_t>(height >> 8),
            static_cast<uint8_t>(height >> 16),
            static_cast<uint8_t>(height >> 24),
            1, 0,                                                 // biPlanes (1)
            static_cast<uint8_t>(bytes_per_pixel * 8), 0,         // biBitCount (24)
            0, 0, 0, 0,                                           // biCompression (0 = BI_RGB)
            static_cast<uint8_t>(image_size),                     // biSizeImage
            static_cast<uint8_t>(image_size >> 8),
            static_cast<uint8_t>(image_size >> 16),
            static_cast<uint8_t>(image_size >> 24),
            0, 0, 0, 0,                                           // biXPelsPerMeter
            0, 0, 0, 0,                                           // biYPelsPerMeter
            0, 0, 0, 0,                                           // biClrUsed
            0, 0, 0, 0                                            // biClrImportant
        };

        out.write(reinterpret_cast<const char*>(file_header), sizeof(file_header));
        out.write(reinterpret_cast<const char*>(info_header), sizeof(info_header));

        const uint8_t padding[3] = {0, 0, 0};

        // BMP standard stores pixels bottom-to-top, in B, G, R order
        for (int y = height - 1; y >= 0; --y) {
            for (int x = 0; x < width; ++x) {
                auto [r, g, b] = at(x, y).to_rgb8(gamma_correct);
                uint8_t bgr[3] = {b, g, r};
                out.write(reinterpret_cast<const char*>(bgr), 3);
            }
            if (padding_size > 0) {
                out.write(reinterpret_cast<const char*>(padding), padding_size);
            }
        }

        return out.good();
    }
};

} // namespace lightrail
