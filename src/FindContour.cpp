#include <set>
#include <utility> // For std::pair

class BoundaryFinder {
public:
    void GetBoundary(std::vector<std::vector<double>>& image) {
        for (int j = 0; j < image[0].size(); j++)
            for (int i = 0; i < image.size(); i++)
                if (image[i][j] == 255)
                    SquareTrace({i, j}, image);
    }

private:
    using Point = std::pair<int, int>;

    void SquareTrace(Point start, std::vector<std::vector<double>>& image) {
        std::set<Point> boundaryPoints;

        boundaryPoints.insert(start);

        Point nextStep = GoLeft({1, 0});
        Point next = {start.first + nextStep.first, start.second + nextStep.second};
        while (next != start) {
            if (image[next.first][next.second] == 0) {
                next.first -= nextStep.first;
                next.second -= nextStep.second;
                nextStep = GoRight(nextStep);
                next.first += nextStep.first;
                next.second += nextStep.second;
            } else {
                boundaryPoints.insert(next);
                nextStep = GoLeft(nextStep);
                next.first += nextStep.first;
                next.second += nextStep.second;
            }
        }
    }

    Point GoLeft(Point p) { return {p.second, -p.first}; }
    Point GoRight(Point p) { return {-p.second, p.first}; }
};
