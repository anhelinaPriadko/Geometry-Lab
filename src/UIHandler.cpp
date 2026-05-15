#include "UIHandler.h"
#include <iostream>
#include <limits>

namespace UIHandler {
    int getVertexCount() {
        int n;
        while (true) {
            std::cout << "Please, enter the number of vertices for the star (minimum 3): ";
            if (std::cin >> n && n >= 3) {
                return n;
            } else {
                std::cout << "Error! Please enter an integer >= 3.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищуємо буфер
            }
        }
    }

    void displayResults(const std::string& filename, double radius) {
        std::cout << "\n" << std::string(40, '=') << "\n";
        std::cout << "Calculation completed successfully!\n";
        std::cout << "File saved: " << filename << "\n";
        std::cout << "Radius of the largest circle: " << radius << "\n";
        std::cout << std::string(40, '=') << "\n";
    }

    void clearConsole() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
}