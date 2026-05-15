#ifndef POLYGON_UTILS_H
#define POLYGON_UTILS_H

#include "Geometry.h"
#include <vector>

std::vector<Point> findKernel(const std::vector<Point>& star);
std::vector<Point> generateRandomStar(int n, Point center, double maxR);

#endif