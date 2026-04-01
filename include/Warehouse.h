#pragma once
#include "Common.h"

class Warehouse {
private:
    int id;
    std::string w_name;
    std::string location;
    int capacity;

public:
    Warehouse(int id, std::string name, std::string loc, int cap) 
        : id(id), w_name(name), location(loc), capacity(cap) {}

    int getID() const { return id; }
    std::string getName() const { return w_name; }
    std::string getLoc() const { return location; }
    int getCap() const { return capacity; }

    std::string toCSV() const {
        return std::to_string(id) + "," + w_name + "," + location + "," + std::to_string(capacity);
    }
};
