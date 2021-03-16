#include "gl2d.h"
#include "params.h"
#include "wtime.h"

#include <algorithm>
#include <cstddef>
#include <unistd.h>

template<bool top_row, typename T>
static void fill_row(const T* manna_row, int limit, int width, int target_height, uint8_t* row_data)
{
    static const uint8_t color_overflow[3] = { 255, 0, 0 };
    static const uint8_t color_empty[3] = { 50, 50, 50 };
    static const uint8_t color_present[3] = { 237, 201, 175 };
    static const uint8_t color_void[3] = { 1, 1, 1 };

    for (int x = 0; x < limit; ++x) {
        if (top_row && (manna_row[x] > target_height)) {
            std::copy_n(color_overflow, 3, &row_data[3 * x]);
        } else if (manna_row[x] >= target_height) {
            std::copy_n(color_present, 3, &row_data[3 * x]);
        } else {
            std::copy_n(color_empty, 3, &row_data[3 * x]);
        }
    }
    for (int x = limit; x < width; ++x) {
        std::copy_n(color_void, 3, &row_data[3 * x]);
    }
}


template<typename T>
static void draw_manna(gl2d_t gl2d, int n, int width, int height, int band_height, const T* manna_data)
{
    static const uint8_t color_void[3] = { 0, 0, 0 };
    static double last_frame = 0.0;

    static const double target_frametime = 1.0 / TARGET_FPS;
    double elapsed_time = wtime() - last_frame;
    if (elapsed_time < target_frametime) {
        usleep(static_cast<useconds_t>((target_frametime - elapsed_time) * 1000.0));
    }
    last_frame = wtime();

    uint8_t *row_data = new uint8_t[width * 3];
    // slow raster
    for (int chunk_start = 0, band_start = 0;
         (chunk_start < n) && (band_start + band_height + 1 < height);
         chunk_start += width, band_start += band_height + 1)
    {
        int limit = std::min(n - chunk_start, width);
        for (int row = band_height; row >= 1; --row) {
            if (row == band_height) {
                fill_row<true>(manna_data + chunk_start, limit, width, row, row_data);
            } else {
                fill_row<false>(manna_data + chunk_start, limit, width, row, row_data);
            }
            gl2d_draw_rgb888(gl2d, 0, band_start + (band_height - row), width, 1, row_data);
        }

        for (int x = 0; x < width; ++x) {
            std::copy_n(color_void, 3, &row_data[3 * x]);
        }
        gl2d_draw_rgb888(gl2d, 0, band_start + band_height, width, 1, row_data);
    }
    gl2d_display(gl2d);
    delete[] row_data;
}
