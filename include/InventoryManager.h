#pragma once
#include "Common.h"
#include "Product.h"
#include "PerishableProduct.h"
#include "Stocks.h"
#include "Warehouse.h"
#include "FileManager.h"
#include "Provider.h"
#include <vector>
#include <memory>
#include <sstream>

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
                bool success = (qtyChange < 0) ? s->deductStock(-qtyChange) : (s->addStock(qtyChange), true);
                if (success) {
                    Product* p = findProductByID(pID);
                    if (p) p->setStock(p->getStock() + qtyChange);
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
        products.clear();
        stocks.clear();

        // Load Products & Perishables
        auto pLines = FileManager::loadFromFile("Product.csv");
        for (const auto& line : pLines) {
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> tokens;
            while(std::getline(ss, item, ',')) tokens.push_back(item);

            if (tokens.size() >= 4) {
                if (tokens.size() == 5) { // It's a Perishable Product
                    products.push_back(std::make_unique<PerishableProduct>(
                        std::stoi(tokens[0]), tokens[1], tokens[2], std::stod(tokens[3]), tokens[4]));
                } else { // Normal Product
                    products.push_back(std::make_unique<Product>(
                        std::stoi(tokens[0]), tokens[1], tokens[2], std::stod(tokens[3])));
                }
            }
        }
        
        // Load Stocks and Sync to Products
        auto sLines = FileManager::loadFromFile("Stocks.csv");
        for (const auto& line : sLines) {
            auto sRec = std::make_unique<Stocks>(Stocks::fromCSV(line));
            Product* p = findProductByID(sRec->getProductID());
            if (p) p->setStock(p->getStock() + sRec->getCount());
            stocks.push_back(std::move(sRec));
        }
        
        UI::printInfo("System loaded " + std::to_string(products.size()) + " products and synced " + std::to_string(stocks.size()) + " locations.");
    }

    void saveAllData() {
        std::vector<std::string> pLines, sLines;
        for (const auto& p : products) pLines.push_back(p->toCSV());
        for (const auto& s : stocks) sLines.push_back(s->toCSV());
        
        FileManager::saveToFile("Product.csv", pLines);
        FileManager::saveToFile("Stocks.csv", sLines);
    }
};
