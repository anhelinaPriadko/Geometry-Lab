#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>

struct Point {
    double x, y;
};

Point subtract(Point a, Point b);
double crossProduct(Point a, Point b);
double length(Point a);
double distToSegment(Point p, Point a, Point b);

#endif