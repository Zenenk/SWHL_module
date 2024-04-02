#include <vector>
#include <set>
#include <utility>

class BoundaryFinder {
public:
    void GetBoundary(std::vector<std::vector<double>>& image, std::set<std::pair<int, int>>& boundaryPoints) {
        for (int j = 0; j < image[0].size(); ++j) {
            for (int i = 0; i < image.size(); ++i) {
                if (image[i][j] == 255) { // Found first white pixel
                    SquareTrace(std::make_pair(i, j), image, boundaryPoints);
                }
            }
        }
    }

private:
    void SquareTrace(std::pair<int, int> start, std::vector<std::vector<double>>& image, 
                    std::set<std::pair<int, int>>& boundaryPoints) {
        boundaryPoints.insert(start);

        std::pair<int, int> nextStep = GoLeft(std::make_pair(1, 0));
        std::pair<int, int> next = {start.first + nextStep.first, start.second + nextStep.second};

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

    std::pair<int, int> GoLeft(std::pair<int, int> p) {
        return std::make_pair(p.second, -p.first);
    }

    std::pair<int, int> GoRight(std::pair<int, int> p) {
        return std::make_pair(-p.second, p.first);
    }
};

