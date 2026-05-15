#ifndef CIRCLE_SOLVER_H
#define CIRCLE_SOLVER_H

#include "Geometry.h"
#include <vector>

struct CircleResult {
    Point center;
    double radius;
};

class CircleSolver {
public:
    static CircleResult findLargest(const std::vector<Point>& star, const std::vector<Point>& kernel);
};

#endif