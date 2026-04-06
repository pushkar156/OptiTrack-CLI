#pragma once
#include "Product.h"

class PerishableProduct : public Product {
private:
    std::string expiryDate;

public:
    PerishableProduct(int id, std::string name, std::string description, double price, std::string expiry)
        : Product(id, name, description, price), expiryDate(expiry) {}

    // Overriding displayDetails (Polymorphism)
    void displayDetails() const override {
        std::cout << std::left << std::setw(6) << getId() 
                  << std::setw(20) << getName() 
                  << std::setw(12) << std::fixed << std::setprecision(2) << getPrice() 
                  << std::setw(15) << expiryDate 
                  << getDesc() << std::endl;
    }

    std::string getExpiry() const { return expiryDate; }

    std::string toCSV() const override {
        return Product::toCSV() + "," + expiryDate;
    }
};
