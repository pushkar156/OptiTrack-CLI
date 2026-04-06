#pragma once
#include "Common.h"

class Order {
private:
    int id;
    std::string orderDate;
    int productID;
    int quantity;
    double price; // Unit price at the time of sale

public:
    Order(int id, std::string date, int pID, int qty, double pr) 
        : id(id), orderDate(date), productID(pID), quantity(qty), price(pr) {}

    double calculateTotal() const {
        return quantity * price;
    }

    void printInvoice() const {
        UI::printHeader("CUSTOMER INVOICE");
        std::cout << "Order ID: " << id << " | Date: " << orderDate << std::endl;
        std::cout << "Product ID: " << productID << " | Qty: " << quantity << std::endl;
        std::cout << "Unit Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << UI::BOLD << "TOTAL AMOUNT: $" << calculateTotal() << UI::RESET << std::endl;
        std::cout << "----------------------------------------------\n" << std::endl;
    }

    std::string toCSV() const {
        return std::to_string(id) + "," + orderDate + "," + std::to_string(productID) + "," + std::to_string(quantity) + "," + std::to_string(price);
    }
};
