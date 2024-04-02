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
  double max_1 = 0;
  double max_2 = 0;
  set <int> :: iterator it_1 = boundaryPoints.begin();

  Point p, lineStart, lineEnd;

  for(int i = 0; i < polygon.size(); i++) {
    for (int k = 1; it_1 != boundaryPoints.end(); k++, it_1++) {
      
      p.x = polygon[i].x;
      p.y = polygon[i].y;;
      lineStart.x = (*it_1).first();
      lineStart.y = (*it_1).second();
      if(it_1 + 1 == boundaryPoints.end()) {
        set <int> :: iterator it = boundaryPoints.begin();
        lineEnd.x = (*it).first();
        lineEnd.y = (*it).second();
      }
      else {
        lineEnd.x = (*(it + 1)).first();
        lineEnd.y = (*(it + 1)).second();
      }

      double cur = perpendicularDistance(p, lineStart, lineEnd);
      if(max_1 < cur) {
        max_1 = cur;
      }

    }
  }
  
  set <int> :: iterator it_2 = boundaryPoints.begin();

  for (int i = 1; it_2 != boundaryPoints.end(); i++, it_2++) {
    for(int i = 0; i < polygon.size(); i++) { 
      Point p, lineStart, lineEnd;
      p.x = (*it_2).first();
      p.y = (*it_2).second();
      lineStart.x = polygon[i].x;
      lineStart.y = polygon[i].y;
      if(i + 1 == polygon.size()) {
        lineEnd.x = polygon[0].x;
        lineEnd.y = polygon[0].y;
      }
      else {
        lineEnd.x = polygon[i + 1].x;
        lineEnd.y = polygon[i + 1].y;
      }

      double cur = perpendicularDistance(p, lineStart, lineEnd);
      if(max_2 < cur) {
        max_2 = cur;
      }

    }
  }

  return std::max(max_1, max_2);
  
}