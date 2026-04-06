#pragma once
#include "Common.h"
#include "Product.h"
#include "PerishableProduct.h"
#include "Stocks.h"
#include "Warehouse.h"
#include "FileManager.h"

class InventoryManager {
private:
    std::vector<std::unique_ptr<Product>> products;
    std::vector<std::unique_ptr<Stocks>> stocks;
    std::vector<std::unique_ptr<Warehouse>> warehouses;

public:
    InventoryManager() { loadAllData(); }
    ~InventoryManager() { saveAllData(); }

    // Core Logical Methods
    void addProduct(std::unique_ptr<Product> product) {
        products.push_back(std::move(product));
        saveAllData();
    }

    Product* findProductByID(int id) {
        for (const auto& p : products) {
            if (p->getId() == id) return p.get();
        }
        return nullptr;
    }

    bool updateStock(int pID, int wID, int qtyChange) {
        for (const auto& s : stocks) {
            if (s->getProductID() == pID && s->getWarehouseID() == wID) {
                if (qtyChange < 0) {
                    if (s->deductStock(-qtyChange)) {
                        saveAllData();
                        return true;
                    }
                } else {
                    s->addStock(qtyChange);
                    saveAllData();
                    return true;
                }
            }
        }
        return false;
    }

    const auto& getProducts() const { return products; }

    // CRUD Loading & Saving
    void loadAllData() {
        // Load Products (Simulated logic for demo)
        auto pLines = FileManager::loadFromFile("Product.csv");
        for (const auto& line : pLines) {
            products.push_back(std::make_unique<Product>(Product::fromCSV(line)));
        }
        
        UI::printInfo("Loaded " + std::to_string(products.size()) + " products from CSV.");
    }

    void saveAllData() {
        std::vector<std::string> pLines;
        for (const auto& p : products) pLines.push_back(p->toCSV());
        FileManager::saveToFile("Product.csv", pLines);
    }
};
