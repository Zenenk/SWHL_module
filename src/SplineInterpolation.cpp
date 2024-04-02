#include <iostream>
#include <vector>
#include <algorithm>


#include <iostream>
#include <vector>
#include <algorithm>

double cubicInterpolate(double p0, double p1, double p2, double p3, double frac) {

    double A = (p3 - p2) - (p0 - p1);
    double B = (p0 - p1) - A;
    double C = p2 - p0;
    double D = p1;

    return D + frac * (C + frac * (B + frac * A));
}

std::vector<std::vector<double>> bicubicInterpolate2D(const std::vector<std::vector<double>>& input, int newHeight, int newWidth) {
    int oldHeight = input.size();
    int oldWidth = input[0].size();
    std::vector<std::vector<double>> temp(oldHeight, std::vector<double>(newWidth));
    std::vector<std::vector<double>> output(newHeight, std::vector<double>(newWidth));
    double scaleX = static_cast<double>(oldWidth - 1) / (newWidth - 1);
    double scaleY = static_cast<double>(oldHeight - 1) / (newHeight - 1);

    // First, interpolate rows
    for (int i = 0; i < oldHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            double x = j * scaleX;
            int xi = static_cast<int>(x);
            double frac = x - xi;
            temp[i][j] = cubicInterpolate(
                input[i][std::max(0, xi - 1)],
                input[i][xi],
                input[i][std::min(oldWidth - 1, xi + 1)],
                input[i][std::min(oldWidth - 1, xi + 2)],
                frac
            );
        }
    }

    // Then, interpolate columns
    for (int j = 0; j < newWidth; ++j) {
        for (int i = 0; i < newHeight; ++i) {
            double y = i * scaleY;
            int yi = static_cast<int>(y);
            double frac = y - yi;
            output[i][j] = cubicInterpolate(
                temp[std::max(0, yi - 1)][j],
                temp[yi][j],
                temp[std::min(oldHeight - 1, yi + 1)][j],
                temp[std::min(oldHeight - 1, yi + 2)][j],
                frac
            );
        }
    }

    return output;
}
