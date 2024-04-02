#include <iostream>
#include <vector>
#include <map>
#include <gdspy.h>
#include <cmath>

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

double perpendicularDistance(const Point& p, const Point& lineStart, const Point& lineEnd) {

    double A = lineEnd.y - lineStart.y;
    double B = lineStart.x - lineEnd.x;
    double C = lineEnd.x * lineStart.y - lineStart.x * lineEnd.y;

    double distance = std::abs(A * p.x + B * p.y + C) / std::sqrt(A * A + B * B);
    return distance;
}

double MaxDeviation(std::vector<Point> polygon, std::set<std::pair<int, int>>& boundaryPoints) {
  int height = img.size();
  int width = img[0].size();
  double min = std::max(height, width);
  
  set <int> :: iterator it = boundaryPoints.begin();
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if()
    }
  }



}