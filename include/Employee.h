#pragma once
#include "Common.h"

class Employee {
private:
    int id;
    std::string ename;
    std::string role;
    Employee* manager; // Hierarchy pointer
    std::vector<Employee*> subordinates; // Downward hierarchy

public:
    Employee(int id, std::string name, std::string role, Employee* mgr = nullptr) 
        : id(id), ename(name), role(role), manager(mgr) {}

    // Add subordinate
    void addSubordinate(Employee* emp) {
        subordinates.push_back(emp);
    }

    // Set Manager
    void setManager(Employee* mgr) {
        manager = mgr;
    }

    // Getters
    int getID() const { return id; }
    std::string getName() const { return ename; }
    std::string getRole() const { return role; }
    Employee* getManager() const { return manager; }
    const std::vector<Employee*>& getSubordinates() const { return subordinates; }

    void displayHierarchy(int indent = 0) const {
        for(int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << "|-- " << UI::BOLD << ename << UI::RESET 
                  << " (" << role << ")" ;
        if(manager) std::cout << " -> Managed by: " << manager->ename;
        std::cout << std::endl;
        
        for(auto sub : subordinates) {
            sub->displayHierarchy(indent + 1);
        }
    }

    std::string toCSV() const {
        int managerID = (manager) ? manager->getID() : -1;
        return std::to_string(id) + "," + ename + "," + role + "," + std::to_string(managerID);
    }
};
