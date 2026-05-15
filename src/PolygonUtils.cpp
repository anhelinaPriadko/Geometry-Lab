#include "PolygonUtils.h"
#include "Geometry.h"
#include <algorithm>
#include <random>

std::vector<Point> findKernel(const std::vector<Point>& star) {
    std::vector<Point> kernel = {{0,0}, {500,0}, {500,500}, {0,500}};
    for (size_t i = 0; i < star.size(); ++i) {
        Point a = star[i];
        Point b = star[(i + 1) % star.size()];
        std::vector<Point> next_poly;
        for (size_t j = 0; j < kernel.size(); ++j) {
            Point p1 = kernel[j];
            Point p2 = kernel[(j + 1) % kernel.size()];
            bool in1 = isLeft(p1, a, b);
            bool in2 = isLeft(p2, a, b);
            if (in1 && in2) next_poly.push_back(p2);
            else if (in1 && !in2) next_poly.push_back(intersect(p1, p2, a, b));
            else if (!in1 && in2) {
                next_poly.push_back(intersect(p1, p2, a, b));
                next_poly.push_back(p2);
            }
        }
        kernel = next_poly;
    }
    return kernel;
}

std::vector<Point> generateRandomStar(int n, Point center, double maxR) {
    std::vector<Point> star;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distR(maxR * 0.3, maxR);
    
    std::vector<double> angles;
    for (int i = 0; i < n; ++i) {
        std::uniform_real_distribution<double> distA(0, 2 * M_PI);
        angles.push_back(distA(gen));
    }
    std::sort(angles.begin(), angles.end());

    for (double a : angles) {
        double r = distR(gen);
        star.push_back({center.x + r * std::cos(a), center.y + r * std::sin(a)});
    }
    return star;
}