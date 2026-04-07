#pragma once
#include "Common.h"

class FileManager {
public:
    // Write all lines to a file (overwrites)
    static bool saveToFile(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream file("data/" + filename);
        if (!file.is_open()) {
            UI::printError("Could not open file for writing: " + filename);
            return false;
        }
        for (const auto& line : lines) {
            file << line << "\n";
        }
        file.close();
        return true;
    }

    // Append a single line to a file
    static bool appendToFile(const std::string& filename, const std::string& line) {
        std::ofstream file("data/" + filename, std::ios::app);
        if (!file.is_open()) {
            UI::printError("Could not open file for appending: " + filename);
            return false;
        }
        file << line << "\n";
        file.close();
        return true;
    }

    // Read all lines from a file
    static std::vector<std::string> loadFromFile(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file("data/" + filename);
        if (!file.is_open()) {
            // File might not exist yet, which is okay for first run
            return lines;
        }
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.find_first_not_of(" \t\n\r") != std::string::npos) {
                lines.push_back(line);
            }
        }
        file.close();
        return lines;
    }
};
