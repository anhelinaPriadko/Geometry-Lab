#include "UIHandler.h"
#include "PolygonUtils.h"
#include "CircleSolver.h"
#include "SvgExporter.h"

int main() {
    UIHandler::clearConsole();
    
    int N = UIHandler::getVertexCount();
    Point center = {250, 250};

    auto star = generateRandomStar(N, center, 200);
    auto kernel = findKernel(star);
    auto result = CircleSolver::findLargest(star, kernel);

    std::string filename = "star_circle.svg";
    saveSvg(filename, star, kernel, result);

    UIHandler::displayResults(filename, result.radius);

    return 0;
}