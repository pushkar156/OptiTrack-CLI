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
        // Logic to load order history if needed
    }

    void saveOrders() {
        std::vector<std::string> lines;
        for (const auto& o : orderHistory) lines.push_back(o->toCSV());
        FileManager::saveToFile("Orders.csv", lines);
    }
};
