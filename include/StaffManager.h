#pragma once
#include "Common.h"
#include "Employee.h"
#include "FileManager.h"
#include <map>

class StaffManager {
private:
    std::vector<std::unique_ptr<Employee>> staff;

public:
    StaffManager() { loadStaff(); }
    ~StaffManager() { saveStaff(); }

    void addEmployee(std::unique_ptr<Employee> emp) {
        staff.push_back(std::move(emp));
        saveStaff();
    }

    void displayAll() const {
        UI::printHeader("ORGANIZATIONAL CHART");
        // Only display those with no managers (CEO level) as roots
        for (const auto& emp : staff) {
            if (emp->getManager() == nullptr) {
                emp->displayHierarchy();
            }
        }
    }

    Employee* findEmployeeByID(int id) {
        for (const auto& emp : staff) {
            if (emp->getID() == id) return emp.get();
        }
        return nullptr;
    }

    void loadStaff() {
        auto lines = FileManager::loadFromFile("Staff.csv");
        std::map<int, int> managerMap; // EmpID -> ManagerID

        // 1. Create all objects first
        for (const auto& line : lines) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> tokens;
            while(std::getline(ss, item, ',')) tokens.push_back(item);

            if (tokens.size() >= 4) {
                int empID = std::stoi(tokens[0]);
                int managerID = std::stoi(tokens[3]);
                staff.push_back(std::make_unique<Employee>(empID, tokens[1], tokens[2]));
                managerMap[empID] = managerID;
            }
        }

        // 2. Link them to form the hierarchy
        for (auto const& [empID, mgrID] : managerMap) {
            if (mgrID != -1) {
                Employee* emp = findEmployeeByID(empID);
                Employee* mgr = findEmployeeByID(mgrID);
                if (emp && mgr) {
                    emp->setManager(mgr);
                    mgr->addSubordinate(emp);
                }
            }
        }
    }

    void saveStaff() {
        std::vector<std::string> lines;
        for (const auto& emp : staff) lines.push_back(emp->toCSV());
        FileManager::saveToFile("Staff.csv", lines);
    }
};
