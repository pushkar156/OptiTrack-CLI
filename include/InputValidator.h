#pragma once
#include "Common.h"
#include <limits>

class InputValidator {
public:
    // Secure integer input
    static int getInteger(const std::string& prompt, int min = 0, int max = 10000) {
        int value;
        while (true) {
            std::cout << UI::YELLOW << prompt << UI::RESET;
            if (std::cin >> value && value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                UI::printError("Invalid input! Please enter a number between " + std::to_string(min) + " and " + std::to_string(max));
            }
        }
    }

    // Secure double/price input
    static double getDouble(const std::string& prompt, double min = 0.0) {
        double value;
        while (true) {
            std::cout << UI::YELLOW << prompt << UI::RESET;
            if (std::cin >> value && value >= min) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                UI::printError("Invalid price/value! Please enter a positive decimal number.");
            }
        }
    }

    // Secure string input (handles spaces)
    static std::string getString(const std::string& prompt) {
        std::string input;
        std::cout << UI::YELLOW << prompt << UI::RESET;
        std::getline(std::cin, input);
        if (input.empty()) {
             std::getline(std::cin, input);
        }
        return input;
    }
};
