#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <memory>

// ANSI Terminal Colors for Premium CLI
namespace UI {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string CYAN = "\033[36m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string BOLD = "\033[1m";
    const std::string REVERSE = "\033[7m";

    inline void clearScreen() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    inline void printHeader(const std::string& title) {
        std::string line(title.length() + 8, '=');
        std::cout << BOLD << CYAN << "\n" << line << RESET << std::endl;
        std::cout << BOLD << CYAN << "||  " << title << "  ||" << RESET << std::endl;
        std::cout << BOLD << CYAN << line << "\n" << RESET << std::endl;
    }

    inline void printBox(const std::string& msg) {
        std::cout << BOLD << BLUE << "+----------------------------------------+" << RESET << std::endl;
        std::cout << BOLD << BLUE << "| " << std::left << std::setw(38) << msg << " |" << RESET << std::endl;
        std::cout << BOLD << BLUE << "+----------------------------------------+" << RESET << std::endl;
    }

    inline void printSuccess(const std::string& msg) {
        std::cout << BOLD << GREEN << " [OK] " << RESET << msg << std::endl;
    }

    inline void printError(const std::string& msg) {
        std::cout << BOLD << RED << " [!]  " << RESET << msg << std::endl;
    }

    inline void printInfo(const std::string& msg) {
        std::cout << BOLD << YELLOW << " [i]  " << RESET << msg << std::endl;
    }
}
