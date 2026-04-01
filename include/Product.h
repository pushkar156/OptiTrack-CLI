#pragma once
#include "Common.h"

class Product {
private:
    int id;
    std::string pname;
    std::string descrip;
    double price;

public:
    Product(int id, std::string name, std::string description, double price);
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return pname; }
    std::string getDesc() const { return descrip; }
    double getPrice() const { return price; }

    // Setters
    void setPrice(double newPrice) { price = newPrice; }
    void setName(const std::string& newName) { pname = newName; }

    // Display
    virtual void displayDetails() const;

    // Serialization for CSV
    virtual std::string toCSV() const;
    static Product fromCSV(const std::string& line);
};
