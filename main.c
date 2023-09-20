#include "raylib.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

#define MANDLE(r, i) mandelbrot((r), (i), (r), (i), 0)

#define MAX_N_OCCUR (50)

bool mandelbrot(double real, double imag, double c_real, double c_imag,
                size_t n_occur) {
    double square_real = (real * real - imag * imag) + c_real;
    double square_imag = (2 * real * imag) + c_imag;

    if (square_real >= DBL_MAX || square_imag >= DBL_MAX) {
        return false;
    }

    if (square_real == 0 && square_imag == 0) {
        return true;
    }

    if (n_occur < MAX_N_OCCUR) {
        return mandelbrot(square_real, square_imag, c_real, c_imag,
                          n_occur + 1);
    }

    return true;
}

int main(int argc, char **argv) {
    const int screen_width = 1920;
    const int screen_height = 1080;

    InitWindow(screen_width, screen_height, "Mandlebrot");

    int center_x = 0;
    int center_y = 0;

    int height = 192;
    int width = 216;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            center_x -=
                ((float)width / (float)screen_width) * GetMouseDelta().x;
            center_y +=
                ((float)height / (float)screen_height) * GetMouseDelta().y;
        }

        int top = center_y + height / 2;
        int bottom = center_y - height / 2;
        int left = center_x - width / 2;
        int right = center_x + width / 2;

        double cell_width = screen_width / (double)(right - left);
        double cell_height = screen_height / (double)(top - bottom);

        width -= 0.01f * (float)(right - left) * GetMouseWheelMove();
        height -= 0.01f * (float)(top - bottom) * GetMouseWheelMove();

        for (int i = top; i > bottom; --i) {
            for (int j = left; j < right; ++j) {
                if (MANDLE((double)j / 100.f, (double)i / 100.f)) {
                    double x = ((double)j - left) / (double)(right - left) *
                               screen_width;
                    double y = ((double)i - top) / (double)(bottom - top) *
                               screen_height;

                    DrawRectangle(x, y, cell_width + 1, cell_height + 1, GRAY);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
