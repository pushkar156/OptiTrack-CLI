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
    const std::string MAGENTA = "\033[35m";
    const std::string BOLD = "\033[1m";

    inline void printHeader(const std::string& title) {
        std::cout << BOLD << CYAN << "\n==============================================" << RESET << std::endl;
        std::cout << BOLD << CYAN << "   " << title << RESET << std::endl;
        std::cout << BOLD << CYAN << "==============================================\n" << RESET << std::endl;
    }

    inline void printSuccess(const std::string& msg) {
        std::cout << GREEN << "[SUCCESS] " << RESET << msg << std::endl;
    }

    inline void printError(const std::string& msg) {
        std::cout << RED << "[ERROR] " << RESET << msg << std::endl;
    }

    inline void printInfo(const std::string& msg) {
        std::cout << YELLOW << "[INFO] " << RESET << msg << std::endl;
    }
}
