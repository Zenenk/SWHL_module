#include <iostream>
#include <vector>
#include <map>

struct Point {
    double x, y;
};
 

bool point_in_polygon(double ximg, double yimg, std::vector<Point> polygon)
{
    int num_vertices = polygon.size();
    double x = ximg, y = yimg;
    bool inside = false;
 
    
    Point p1 = polygon[0], p2;
    for (int i = 1; i <= num_vertices; i++) {
        p2 = polygon[i % num_vertices];
 
        if (y > min(p1.y, p2.y)) {
            if (y <= max(p1.y, p2.y)) {
                if (x <= max(p1.x, p2.x)) {
                    double x_intersection
                        = (y - p1.y) * (p2.x - p1.x)
                              / (p2.y - p1.y)
                          + p1.x;
                    if (p1.x == p2.x
                        || x <= x_intersection) {
                        inside = !inside;
                    }
                }
            }
        }
        p1 = p2;
    }
    return inside;
}

int SymmetricDifference(std::vector<std::vector<double>>& img, std::vector<Point> polygon) {
    int height = input.size();
    int width = input[0].size();
    int count_pixels = 0;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if ((point_in_polygon(i, j, polygon) && img[i][j] == 0) || (!point_in_polygon(i, j, polygon) && img[i][j] == 255)) {
                count++;
            }

        }
    }

    return count;
}

