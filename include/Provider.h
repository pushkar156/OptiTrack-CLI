#pragma once
#include "Common.h"

class Provider {
private:
    int id;
    int supplierID;
    int productID;

public:
    Provider(int id, int sID, int pID) 
        : id(id), supplierID(sID), productID(pID) {}

    // Getters
    int getID() const { return id; }
    int getSupplierID() const { return supplierID; }
    int getProductID() const { return productID; }

    void getProviderInfo() const {
        std::cout << "Provider ID: " << id 
                  << " | Supplier ID: " << supplierID 
                  << " | Product ID: " << productID << std::endl;
    }

    // CSV Serialization
    std::string toCSV() const {
        return std::to_string(id) + "," + std::to_string(supplierID) + "," + std::to_string(productID);
    }

    static Provider fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;
        while (std::getline(ss, item, ',')) tokens.push_back(item);
        if (tokens.size() >= 3) {
            return Provider(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]));
        }
        return Provider(0, 0, 0);
    }
};
