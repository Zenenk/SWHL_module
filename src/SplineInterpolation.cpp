#include <iostream>
#include <vector>
#include <algorithm>


float cubicInterpolate(float p0, float p1, float p2, float p3, float frac) {
    
    float A = (p3 - p2) - (p0 - p1);
    float B = (p0 - p1) - A;
    float C = p2 - p0;
    float D = p1;

    return D + frac * (C + frac * (B + frac * A));
}

std::vector<std::vector<float>> bicubicInterpolate2D(const std::vector<std::vector<float>>& input, int newSize) {
    int oldSize = input.size();
    std::vector<std::vector<float>> temp(oldSize, std::vector<float>(newSize));
    std::vector<std::vector<float>> output(newSize, std::vector<float>(newSize));
    float scale = static_cast<float>(oldSize - 1) / (newSize - 1);

    // First, interpolate rows
    for (int i = 0; i < oldSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            float x = j * scale;
            int xi = static_cast<int>(x);
            float frac = x - xi;
            temp[i][j] = cubicInterpolate(
                input[i][std::max(0, xi - 1)],
                input[i][xi],
                input[i][std::min(oldSize - 1, xi + 1)],
                input[i][std::min(oldSize - 1, xi + 2)],
                frac
            );
        }
    }

    // Then, interpolate columns
    for (int j = 0; j < newSize; ++j) {
        for (int i = 0; i < newSize; ++i) {
            float y = i * scale;
            int yi = static_cast<int>(y);
            float frac = y - yi;
            output[i][j] = cubicInterpolate(
                temp[std::max(0, yi - 1)][j],
                temp[yi][j],
                temp[std::min(oldSize - 1, yi + 1)][j],
                temp[std::min(oldSize - 1, yi + 2)][j],
                frac
            );
        }
    }

    return output;
}
