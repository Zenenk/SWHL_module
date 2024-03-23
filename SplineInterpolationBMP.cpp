#include <vector>
#include <algorithm>
#include <cmath>

class ImageInterpolator {
public:
    struct RGB {
        unsigned char channels[3];
    };

    static std::vector<RGB> BicubicInterpolation(const std::vector<RGB>& image, int originSizeX, int originSizeY, int newSizeX, int newSizeY) {
        std::vector<RGB> output(newSizeX * newSizeY);
        float ratioX = static_cast<float>(originSizeX) / newSizeX;
        float ratioY = static_cast<float>(originSizeY) / newSizeY;

        for (int y = 0; y < newSizeY; ++y) {
            for (int x = 0; x < newSizeX; ++x) {
                for (int channel = 0; channel < 3; ++channel) {
                    float xMappingToOrigin = x * ratioX;
                    float yMappingToOrigin = y * ratioY;
                    int xFloor = static_cast<int>(floor(xMappingToOrigin));
                    int yFloor = static_cast<int>(floor(yMappingToOrigin));
                    float xFrac = xMappingToOrigin - xFloor;
                    float yFrac = yMappingToOrigin - yFloor;

                    std::vector<unsigned char> ndata(16);
                    for (int dy = -1; dy <= 2; ++dy) {
                        for (int dx = -1; dx <= 2; ++dx) {
                            int xIndex = clip(xFloor + dx, 0, originSizeX - 1);
                            int yIndex = clip(yFloor + dy, 0, originSizeY - 1);
                            ndata[(dy + 1) * 4 + (dx + 1)] = image[yIndex * originSizeX + xIndex].channels[channel];
                        }
                    }

                    unsigned char result = BicubicPolate(ndata.data(), xFrac, yFrac);
                    output[y * newSizeX + x].channels[channel] = result;
                }
            }
        }
        return output;
    }

private:
    static unsigned char BicubicPolate(const unsigned char* const ndata, const float fracX, const float fracY) {
        float x1 = CubicPolate(ndata[0], ndata[1], ndata[2], ndata[3], fracX);
        float x2 = CubicPolate(ndata[4], ndata[5], ndata[6], ndata[7], fracX);
        float x3 = CubicPolate(ndata[8], ndata[9], ndata[10], ndata[11], fracX);
        float x4 = CubicPolate(ndata[12], ndata[13], ndata[14], ndata[15], fracX);

        float output = clip_float(CubicPolate(x1, x2, x3, x4, fracY), 0.0f, 255.0f);
        return static_cast<unsigned char>(output);
    }

    static float CubicPolate(const float v0, const float v1, const float v2, const float v3, const float frac) {
        float A = (v3 - v2) - (v0 - v1);
        float B = (v0 - v1) - A;
        float C = v2 - v0;
        float D = v1;
        return D + frac * (C + frac * (B + frac * A));
    }

    static int clip(const int input, const int lowerBound, const int upperBound) {
        return std::max(lowerBound, std::min(input, upperBound));
    }

    static float clip_float(const float input, const float lowerBound, const float upperBound) {
        return std::max(lowerBound, std::min(input, upperBound));
    }
};