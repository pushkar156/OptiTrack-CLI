#pragma once
#include "Common.h"

class Product {
private:
    int id;
    std::string pname;
    std::string descrip;
    double price;
    int stockCount;

public:
    Product(int id, std::string name, std::string description, double price, int stock = 0);
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return pname; }
    std::string getDesc() const { return descrip; }
    double getPrice() const { return price; }
    int getStock() const { return stockCount; }

    // Setters
    void setPrice(double newPrice) { price = newPrice; }
    void setName(const std::string& newName) { pname = newName; }
    void setStock(int s) { stockCount = s; }

    // Display
    virtual void displayDetails() const;

    // Serialization for CSV
    virtual std::string toCSV() const;
    static Product fromCSV(const std::string& line);
};
