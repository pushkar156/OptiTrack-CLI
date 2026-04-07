#pragma once
#include "Common.h"
#include "Order.h"
#include "InventoryManager.h"
#include "FileManager.h"

class OrderProcessor {
private:
    std::vector<std::unique_ptr<Order>> orderHistory;
    InventoryManager* invMgr;

public:
    OrderProcessor(InventoryManager* mgr) : invMgr(mgr) { loadOrders(); }
    ~OrderProcessor() { saveOrders(); }

    bool processSale(int productID, int warehouseID, int quantity) {
        Product* p = invMgr->findProductByID(productID);
        if (!p) {
            UI::printError("Product not found!");
            return false;
        }

        // 1. Attempt stock deduction
        if (invMgr->updateStock(productID, warehouseID, -quantity)) {
            // 2. Create the Order
            int nextID = 1000 + orderHistory.size();
            auto newOrder = std::make_unique<Order>(nextID, "2026-04-06", productID, quantity, p->getPrice());
            
            // 3. Print the Result
            UI::printSuccess("Transaction Successful!");
            newOrder->printInvoice();
            
            orderHistory.push_back(std::move(newOrder));
            saveOrders();
            return true;
        } else {
            UI::printError("Insufficient stock in warehouse " + std::to_string(warehouseID));
            return false;
        }
    }

    void loadOrders() {
        auto lines = FileManager::loadFromFile("Orders.csv");
        for (const auto& line : lines) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> tokens;
            while(std::getline(ss, item, ',')) tokens.push_back(item);

            if (tokens.size() >= 5) {
                orderHistory.push_back(std::make_unique<Order>(
                    std::stoi(tokens[0]), tokens[1], std::stoi(tokens[2]), 
                    std::stoi(tokens[3]), std::stod(tokens[4])));
            }
        }
        UI::printInfo("Loaded " + std::to_string(orderHistory.size()) + " previous transactions.");
    }

    void displayFinanceReport() {
        UI::clearScreen();
        UI::printHeader("FINANCIAL PERFORMANCE REPORT");
        
        double totalRevenue = 0.0;
        int totalUnits = 0;

        std::cout << UI::BOLD << "| ID   | DATE       | PROD ID | QTY | TOTAL AMT  |" << UI::RESET << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        
        for (const auto& o : orderHistory) {
            double amount = o->calculateTotal();
            totalRevenue += amount;
            totalUnits += o->getQuantity();
            
            std::cout << "| " << std::left << std::setw(5) << o->getId() << "| " 
                      << std::setw(11) << o->getDate() << "| " 
                      << std::setw(8) << o->getProductID() << "| " 
                      << std::setw(4) << o->getQuantity() << "| $" 
                      << std::setw(10) << std::fixed << std::setprecision(2) << amount << " |" << std::endl;
        }

        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << UI::BOLD << UI::CYAN << ">> TOTAL COMPLETED SALES: " << orderHistory.size() << UI::RESET << std::endl;
        std::cout << UI::BOLD << UI::GREEN << ">> GROSS TOTAL REVENUE:   $" << totalRevenue << UI::RESET << std::endl;
        std::cout << "\n  [Average Order Value: $" << (orderHistory.empty() ? 0 : totalRevenue/orderHistory.size()) << "]" << std::endl;
    }

    void saveOrders() {
        std::vector<std::string> lines;
        for (const auto& o : orderHistory) lines.push_back(o->toCSV());
        FileManager::saveToFile("Orders.csv", lines);
    }
};
