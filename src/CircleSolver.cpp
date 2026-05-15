#include "CircleSolver.h"
#include <limits>
#include <algorithm>

CircleResult CircleSolver::findLargest(const std::vector<Point>& star, const std::vector<Point>& kernel) {
    CircleResult res = {{0, 0}, 0.0};
    if (kernel.empty()) return res;

    double minX = 500, maxX = 0, minY = 500, maxY = 0;
    for(auto p : kernel) {
        minX = std::min(minX, p.x); maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y); maxY = std::max(maxY, p.y);
    }

    const int steps = 150;
    for (int i = 0; i <= steps; ++i) {
        for (int j = 0; j <= steps; ++j) {
            Point cand = {minX + i*(maxX-minX)/steps, minY + j*(maxY-minY)/steps};
            
            bool inside = true;
            for(size_t k=0; k<kernel.size(); ++k) {
                if(!isLeft(cand, kernel[k], kernel[(k+1)%kernel.size()])) {
                    inside = false; break;
                }
            }

            if (inside) {
                double minD = std::numeric_limits<double>::max();
                for (size_t k = 0; k < star.size(); ++k) {
                    minD = std::min(minD, distToSegment(cand, star[k], star[(k+1)%star.size()]));
                }
                if (minD > res.radius) {
                    res.radius = minD;
                    res.center = cand;
                }
            }
        }
    }
    return res;
}