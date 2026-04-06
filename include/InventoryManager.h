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
        // Load Products & Perishables
        auto pLines = FileManager::loadFromFile("Product.csv");
        for (const auto& line : pLines) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> tokens;
            while(std::getline(ss, item, ',')) tokens.push_back(item);

            if (tokens.size() == 5) { // It's a Perishable Product
                products.push_back(std::make_unique<PerishableProduct>(
                    std::stoi(tokens[0]), tokens[1], tokens[2], std::stod(tokens[3]), tokens[4]));
            } else if (tokens.size() == 4) { // Normal Product
                products.push_back(std::make_unique<Product>(
                    std::stoi(tokens[0]), tokens[1], tokens[2], std::stod(tokens[3])));
            }
        }
        
        // Load Stocks
        auto sLines = FileManager::loadFromFile("Stocks.csv");
        for (const auto& line : sLines) {
            stocks.push_back(std::make_unique<Stocks>(Stocks::fromCSV(line)));
        }
        
        UI::printInfo("System loaded " + std::to_string(products.size()) + " products and " + std::to_string(stocks.size()) + " stock records.");
    }

    void saveAllData() {
        std::vector<std::string> pLines;
        for (const auto& p : products) pLines.push_back(p->toCSV());
        FileManager::saveToFile("Product.csv", pLines);
    }
};
