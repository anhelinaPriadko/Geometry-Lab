#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <random>

struct Point {
    double x, y;
};

Point operator-(Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
double cross_product(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double length(Point a) { return std::sqrt(a.x * a.x + a.y * a.y); }

double distToSegment(Point p, Point a, Point b) {
    double l2 = std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2);
    if (l2 == 0.0) return length(p - a);
    double t = std::max(0.0, std::min(1.0, ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / l2));
    Point proj = { a.x + t * (b.x - a.x), a.y + t * (b.y - a.y) };
    return length(p - proj);
}

bool isLeft(Point p, Point a, Point b) {
    return cross_product(b - a, p - a) >= -1e-9;
}

Point intersect(Point a, Point b, Point c, Point d) {
    double a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1 * a.x + b1 * a.y;
    double a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2 * c.x + b2 * c.y;
    double det = a1 * b2 - a2 * b1;
    if (std::abs(det) < 1e-9) return a; 
    return {(b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det};
}

std::vector<Point> findKernel(const std::vector<Point>& star) {
    std::vector<Point> kernel = {{0,0}, {500,0}, {500,500}, {0,500}}; // Початкове робоче поле
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

int main() {
    int N = 12; // Кількість променів
    Point canvasCenter = {250, 250};
    std::vector<Point> star = generateRandomStar(N, canvasCenter, 200);

    // 2. ЗНАХОДИМО ЯДРО
    std::vector<Point> kernel = findKernel(star);

    // 3. ПОШУК ЦЕНТРУ КОЛА (сіткою всередині ядра)
    Point bestCenter = canvasCenter;
    double maxRadius = 0;

    if (!kernel.empty()) {
        double minX = 500, maxX = 0, minY = 500, maxY = 0;
        for(auto p : kernel) {
            minX = std::min(minX, p.x); maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y); maxY = std::max(maxY, p.y);
        }

        int steps = 100; 
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
                    double minD = 1e9;
                    for (size_t k = 0; k < star.size(); ++k) {
                        minD = std::min(minD, distToSegment(cand, star[k], star[(k+1)%star.size()]));
                    }
                    if (minD > maxRadius) {
                        maxRadius = minD;
                        bestCenter = cand;
                    }
                }
            }
        }
    }

    // 4. SVG ВИВІД
    std::ofstream out("star_circle.svg");
    out << "<svg width='500' height='500' xmlns='http://www.w3.org/2000/svg'>\n";
    out << "<rect width='100%' height='100%' fill='#ffffff' />\n";
    
    // Малюємо зірку
    out << "<polygon points='";
    for(auto p : star) out << p.x << "," << p.y << " ";
    out << "' fill='#eeeeee' stroke='#888' stroke-width='1' />\n";

    // Малюємо ядро (напівпрозоре зелене)
    if(!kernel.empty()) {
        out << "<polygon points='";
        for(auto p : kernel) out << p.x << "," << p.y << " ";
        out << "' fill='rgba(0, 255, 0, 0.2)' />\n";
    }

    // Малюємо коло
    if (maxRadius > 0) {
        out << "<circle cx='" << bestCenter.x << "' cy='" << bestCenter.y << "' r='" << maxRadius << "' stroke='red' fill='none' stroke-width='2' />\n";
        out << "<circle cx='" << bestCenter.x << "' cy='" << bestCenter.y << "' r='3' fill='red' />\n";
    }
    out << "</svg>";
    out.close();

    std::cout << "SVG створено. Радіус кола: " << maxRadius << std::endl;
    return 0;
}