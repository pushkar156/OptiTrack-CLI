#pragma once
#include "Common.h"

class Stocks {
private:
    int stockID;
    int productID;
    int warehouseID;
    int stockCount;

public:
    Stocks(int sID, int pID, int wID, int initialStock) 
        : stockID(sID), productID(pID), warehouseID(wID), stockCount(initialStock) {}

    // Methods
    bool deductStock(int qty) {
        if (stockCount >= qty) {
            stockCount -= qty;
            return true;
        }
        return false;
    }

    void addStock(int qty) {
        stockCount += qty;
    }

    // Getters
    int getID() const { return stockID; }
    int getProductID() const { return productID; }
    int getWarehouseID() const { return warehouseID; }
    int getCount() const { return stockCount; }

    // Serialization
    std::string toCSV() const {
        return std::to_string(stockID) + "," + std::to_string(productID) + "," + std::to_string(warehouseID) + "," + std::to_string(stockCount);
    }

    static Stocks fromCSV(const std::string& line) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;
        while (std::getline(ss, item, ',')) tokens.push_back(item);
        if (tokens.size() >= 4) {
            return Stocks(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
        }
        return Stocks(0,0,0,0);
    }
};
