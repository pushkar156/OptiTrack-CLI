#pragma once
#include "Product.h"

class PerishableProduct : public Product {
private:
    std::string expiryDate;

public:
    PerishableProduct(int id, std::string name, std::string description, double price, std::string expiry, int stock = 0)
        : Product(id, name, description, price, stock), expiryDate(expiry) {}

    // Overriding displayDetails (Polymorphism)
    void displayDetails() const override {
        std::string descWithExpiry = "[EXP: " + expiryDate + "] " + getDesc();
        std::cout << std::left << std::setw(5) << getId() << "| " 
                  << std::setw(21) << getName() << "| " 
                  << std::setw(7) << getStock() << "| " 
                  << std::setw(10) << std::fixed << std::setprecision(2) << getPrice() << "| " 
                  << std::setw(30) << (descWithExpiry.length() > 30 ? descWithExpiry.substr(0, 27) + "..." : descWithExpiry) << " |" << std::endl;
    }

    std::string getExpiry() const { return expiryDate; }

    std::string toCSV() const override {
        return Product::toCSV() + "," + expiryDate;
    }
};
