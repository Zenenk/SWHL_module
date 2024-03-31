#include "contour-tracing.h"

pixel * mooreNeighborTracing(pixel * image, int width, int height) {
	bool inside = false;
	int pos = 0;

	// Need to start by padding the image by 1 pixel
	pixel * paddedImage = padImage(image, width, height, WHITE);

	// Allocate new image as a 1D array
	pixel * borderImage = (pixel *)malloc(sizeof(pixel) * (height+2) * (width+2));

	// Set entire image to WHITE
	for(int y = 0; y < (height+2); y ++) {
		for(int x = 0; x < (width+2); x ++) {
			borderImage[x + y*(width+2)] = WHITE;
		}
	}

	for(int y = 0; y < (height+2); y ++) {
		for(int x = 0; x < (width+2); x ++) {
			pos = x + y*(width+2);

			// Scan for BLACK pixel
			if(borderImage[pos] == BLACK && !inside) {		// Entering an already discovered border
				inside = true;
			}
			else if(paddedImage[pos] == BLACK && inside) {	// Already discovered border point
				continue;
			}
			else if(paddedImage[pos] == WHITE && inside) {	// Leaving a border
				inside = false;
			}
			else if(paddedImage[pos] == BLACK && !inside) {	// Undiscovered border point
				borderImage[pos] = BLACK; 	// Mark the start pixel
				int checkLocationNr = 1;	// The neighbor number of the location we want to check for a new border point
				int checkPosition;			// The corresponding absolute array address of checkLocationNr
				int newCheckLocationNr; 	// Variable that holds the neighborhood position we want to check if we find a new border at checkLocationNr
				int startPos = pos;			// Set start position
				int counter = 0; 			// Counter is used for the jacobi stop criterion
				int counter2 = 0; 			// Counter2 is used to determine if the point we have discovered is one single point

				// Defines the neighborhood offset position from current position and the neighborhood
				// position we want to check next if we find a new border at checkLocationNr
				int neighborhood[8][2] = {
						{-1,7},
						{-3-width,7},
						{-width-2,1},
						{-1-width,1},
						{1,3},
						{3+width,3},
						{width+2,5},
						{1+width,5}
				};
				// Trace around the neighborhood
				while(true)
				{
					checkPosition = pos + neighborhood[checkLocationNr-1][0];
					newCheckLocationNr = neighborhood[checkLocationNr-1][1];

					if(paddedImage[checkPosition] == BLACK) { // Next border point found
						if(checkPosition == startPos) {
							counter ++;

							// Stopping criterion (jacob)
							if(newCheckLocationNr == 1 || counter >= 3) {
								// Close loop
								inside = true; // Since we are starting the search at were we first started we must set inside to true
								break;
							}
						}

						checkLocationNr = newCheckLocationNr; // Update which neighborhood position we should check next
						pos = checkPosition;
						counter2 = 0; 						// Reset the counter that keeps track of how many neighbors we have visited
						borderImage[checkPosition] = BLACK; // Set the border pixel
					}
					else {
						// Rotate clockwise in the neighborhood
						checkLocationNr = 1 + (checkLocationNr % 8);
						if(counter2 > 8) {
							// If counter2 is above 8 we have traced around the neighborhood and
							// therefor the border is a single black pixel and we can exit
							counter2 = 0;
							break;
						}
						else {
							counter2 ++;
						}
					}
				}
			}
		}
	}

	// Remove white padding and return it
	pixel * clippedBorderImage = (pixel *)malloc(sizeof(pixel) * (height) * (width));
	for(int x = 0; x < width; x ++) {
		for(int y = 0; y < height; y ++) {
			clippedBorderImage[x+y*width] = borderImage[x+1+(y+1)*(width+2)];
		}
	}
	return clippedBorderImage;
}

/**
 * Check to see if to pixels are equal
 */
bool pixel::operator==(const pixel &other) {
	return r == other.r && b == other.b && g == other.g;
}

/**
 * Pads an image represented by a 1D pixel array with 1 pixel with a color
 * specified by paddingColor
 */
pixel * padImage(pixel * image, int width, int height, pixel paddingColor) {
	pixel * paddedImage = (pixel *)malloc(sizeof(pixel) * (height+2) * (width+2));
	for(int x = 0; x < width+2; x ++) {
		for(int y = 0; y < height+2; y ++) {
			if(x == 0 || y == 0 || x == width+1 || y == height+1) {
				paddedImage[x + y*(width+2)] = paddingColor;
			}
			else {
				paddedImage[x+y*(width+2)] = image[x-1 + (y-1)*width];
			}
		}
	}
	return paddedImage;
}

void binarizeImage(std::vector<std::vector<uint8_t>>& image, int h) {
    int rows = image.size();
    int cols = image[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (image[i][j] < h) {
                image[i][j] = 0; // Set to black
            }
            else {
                image[i][j] = 255; // Set to white
            }
        }
    }
}

