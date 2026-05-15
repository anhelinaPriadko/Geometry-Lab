#include "Geometry.h"
#include <algorithm>

Point subtract(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}

double crossProduct(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double length(Point a) {
    return std::sqrt(a.x * a.x + a.y * a.y);
}

double distToSegment(Point p, Point a, Point b) {
    Point ab = {b.x - a.x, b.y - a.y};
    double l2 = ab.x * ab.x + ab.y * ab.y;
    if (l2 == 0.0) return length({p.x - a.x, p.y - a.y});
    
    double t = std::max(0.0, std::min(1.0, ((p.x - a.x) * ab.x + (p.y - a.y) * ab.y) / l2));
    Point proj = {a.x + t * ab.x, a.y + t * ab.y};
    return length({p.x - proj.x, p.y - proj.y});
}

Point intersect(Point a, Point b, Point c, Point d) {
    double a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1 * a.x + b1 * a.y;
    double a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2 * c.x + b2 * c.y;
    double det = a1 * b2 - a2 * b1;
    if (std::abs(det) < 1e-9) return a; 
    return {(b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det};
}

bool isLeft(Point p, Point a, Point b) {
    return crossProduct({b.x - a.x, b.y - a.y}, {p.x - a.x, p.y - a.y}) >= -1e-9;
}