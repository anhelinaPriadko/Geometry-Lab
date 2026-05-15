#include "SvgExporter.h"
#include <fstream>

void saveSvg(const std::string& filename, 
             const std::vector<Point>& star, 
             const std::vector<Point>& kernel, 
             CircleResult circle) {
    std::ofstream out(filename);
    out << "<svg width='500' height='500' xmlns='http://www.w3.org/2000/svg'>\n";
    out << "<rect width='100%' height='100%' fill='#fdfdfd' />\n";
    
    out << "<polygon points='";
    for(auto p : star) out << p.x << "," << p.y << " ";
    out << "' fill='#f0f0f0' stroke='#999' stroke-width='0.2' />\n";

    if(!kernel.empty()) {
        out << "<polygon points='";
        for(auto p : kernel) out << p.x << "," << p.y << " ";
        out << "' fill='rgba(76, 175, 80, 0.2)' stroke='green' stroke-width='0.2' />\n";
    }

    if (circle.radius > 0) {
        out << "<circle cx='" << circle.center.x << "' cy='" << circle.center.y << "' r='" << circle.radius << "' stroke='#d32f2f' fill='none' stroke-width='0.2' />\n";
        out << "<circle cx='" << circle.center.x << "' cy='" << circle.center.y << "' r='1.5' fill='#d32f2f' />\n";
    }
    
    out << "</svg>";
    out.close();
}