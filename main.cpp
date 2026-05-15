#include <iostream>
#include "PolygonUtils.h"
#include "CircleSolver.h"
#include "SvgExporter.h"

int main() {
    int N = 12;
    Point center = {250, 250};

    auto star = generateRandomStar(N, center, 200);
    auto kernel = findKernel(star);
    auto result = CircleSolver::findLargest(star, kernel);

    saveSvg("result.svg", star, kernel, result);

    std::cout << "Done!" << std::endl;
    return 0;
}