#include <iostream>
#include <vector>

void binarizeImage(std::vector<std::vector<uint8_t>>& image, int h) {
    int rows = image.size();
    int cols = image[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (image[i][j] > h) {
                image[i][j] = 0; // Set to black
            }
            else {
                image[i][j] = 255; // Set to white
            }
        }
    }
}