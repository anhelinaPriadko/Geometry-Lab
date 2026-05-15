#ifndef UI_HANDLER_H
#define UI_HANDLER_H

#include <string>

namespace UIHandler {
    int getVertexCount();

    void displayResults(const std::string& filename, double radius);

    void clearConsole();
}

#endif