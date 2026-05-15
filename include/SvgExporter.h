#ifndef SVG_EXPORTER_H
#define SVG_EXPORTER_H

#include "Geometry.h"
#include "CircleSolver.h"
#include <vector>
#include <string>

void saveSvg(const std::string& filename, 
             const std::vector<Point>& star, 
             const std::vector<Point>& kernel, 
             CircleResult circle);

#endif