#pragma once
#include "Common.h"
#include "InventoryManager.h"
#include "StaffManager.h"
#include "OrderProcessor.h"
#include "InputValidator.h"

class MenuSystem {
private:
    InventoryManager invMgr;
    StaffManager staffMgr;
    OrderProcessor ordProc;
    std::string currentRole;

public:
    MenuSystem() : ordProc(&invMgr) {}

    void start() {
        while (true) {
            UI::clearScreen();
            // 1. System Status Bar
            std::cout << UI::REVERSE << UI::CYAN << "  SYSTEM STATUS: ONLINE  |  V2.2.0  |  SECURITY: [ENCRYPTED]  |  AUTH: [PENDING]  " << UI::RESET << "\n\n";

            // 2. Gradient Logo
            std::cout << UI::BOLD << UI::BLUE  << "  ____        _   " << UI::CYAN << "_ _______                     \n"
                      << UI::BLUE  << " / __ \\      | | " << UI::CYAN << "(_)__   __|                    \n"
                      << UI::BLUE  << "| |  | |_ __ | |_ _   | |_ __ __ _  ___ | | __  \n"
                      << UI::BLUE  << "| |  | | '_ \\| __| |  | | '__/ _` |/ __|| |/ /  \n"
                      << UI::BLUE  << "| |__| | |_) | |_| |  | | | | (_| | (__ |   <   \n"
                      << UI::BLUE  << " \\____/| .__/ \\__|_|  |_|_|  \\__,_|\\___||_|\\_\\ \n"
                      << UI::BLUE  << "       | |                                      \n"
                      << UI::BLUE  << "       |_|                                      " << UI::RESET << std::endl;

            UI::printBox("CENTRAL LOGISTICS COMMAND");
            std::cout << UI::BOLD << "  [1] " << UI::RESET << "Secure Admin Login" << std::endl;
            std::cout << UI::BOLD << "  [2] " << UI::RESET << "Warehouse Logistics Hub" << std::endl;
            std::cout << UI::BOLD << "  [3] " << UI::RESET << "Point-of-Sale Access" << std::endl;
            std::cout << UI::BOLD << "  [0] " << UI::RESET << UI::RED << "Shut Down Protocol" << UI::RESET << std::endl;

            // 3. Pulse Footer
            std::cout << UI::CYAN << "\n  >> DATABASE: STABLE | ITEMS: " << invMgr.getProducts().size() << " | SYNC: ACTIVE" << UI::RESET << std::endl;

            int choice = InputValidator::getInteger("\n  Enter Protocol ID: ", 0, 3);
            if (choice == 0) break;

            if (choice == 1) login("Admin");
            else if (choice == 2) login("Warehouse Manager");
            else if (choice == 3) login("Sales Staff");
        }
    }

private:
    void login(std::string role) {
        UI::clearScreen();
        UI::printHeader("AUTHENTICATION SUCCESSFUL");
        UI::printInfo("Access level: " + role);
        currentRole = role;
        showMainMenu();
    }

    void showMainMenu() {
        while (true) {
            UI::clearScreen();
            
            // Role Banner
            std::cout << UI::REVERSE << UI::CYAN << "  LOGGED IN AS: " << std::left << std::setw(20) << currentRole << " | SESSION: ACTIVE  " << UI::RESET << "\n\n";
            
            UI::printHeader(currentRole + " Main Menu");
            UI::printBox("ACTIVE DATA SECTIONS");
            std::cout << UI::BOLD << "  1. " << UI::RESET << "Open Stock Inventory" << std::endl;
            
            // RBAC logic for menu options
            if (currentRole == "Admin" || currentRole == "Warehouse Manager") {
                std::cout << UI::BOLD << "  2. " << UI::RESET << "Logistics: Update Stock" << std::endl;
                std::cout << UI::BOLD << "  3. " << UI::RESET << "Warehouse: Low Stock Sentinel" << std::endl;
            }
            if (currentRole == "Admin") {
                std::cout << UI::BOLD << "  4. " << UI::RESET << "Supply: Provider Records" << std::endl;
            }
            if (currentRole == "Admin" || currentRole == "Sales Staff") {
                std::cout << UI::BOLD << "  5. " << UI::RESET << "POS: Process Transaction" << std::endl;
            }
            if (currentRole == "Admin") {
                std::cout << UI::BOLD << "  6. " << UI::RESET << "Finance: Analytics Report" << std::endl;
                std::cout << UI::BOLD << "  7. " << UI::RESET << "Arrival: New Product Entry" << std::endl;
                std::cout << UI::BOLD << "  8. " << UI::RESET << "HR: Staff Hierarchy" << std::endl;
            }

            std::cout << UI::BOLD << "  0. " << UI::RESET << UI::RED << "End Secure Session" << UI::RESET << std::endl;

            int choice = InputValidator::getInteger("\n  Execute Action ID: ", 0, 8);
            if (choice == 0) break;

            handleAction(choice);
        }
    }

    void handleAction(int choice) {
        switch (choice) {
            case 1:
                displayInventory();
                break; // displayInventory has its own pause
            case 2:
                if (currentRole != "Sales Staff") updateStock();
                else UI::printError("Access Denied for Sales Staff!");
                pause();
                break;
            case 3:
                invMgr.displayLowStockAlerts();
                pause();
                break;
            case 4:
                if (currentRole == "Admin") invMgr.displayProviders();
                else UI::printError("Access restricted!");
                pause();
                break;
            case 5:
                processSale();
                pause();
                break;
            case 6:
                if (currentRole == "Admin") ordProc.displayFinanceReport();
                else UI::printError("Access Restricted!");
                pause();
                break;
            case 7:
                if (currentRole == "Admin") registerProduct();
                else UI::printError("Access Restricted!");
                pause();
                break;
            case 8:
                if (currentRole == "Admin") staffMgr.displayAll();
                else UI::printError("Access restricted!");
                pause();
                break;
            default:
                UI::printInfo("Feature coming soon in full release!");
                pause();
        }
    }

    void registerProduct() {
        UI::clearScreen();
        UI::printHeader("NEW PRODUCT ENTRY");
        int pID = 100 + invMgr.getProducts().size() + 1;
        std::string name = InputValidator::getString("  Product Name: ");
        std::string desc = InputValidator::getString("  Description:  ");
        double price = InputValidator::getInteger("  Price ($):    ", 1, 100000);
        int initialStock = InputValidator::getInteger("  Initial Stock:", 1, 1000);
        
        invMgr.registerNewProduct(pID, name, desc, price, initialStock, 1);
    }

    void pause() {
        std::cout << UI::YELLOW << "\n  [Press Enter to continue...]" << UI::RESET;
        std::cin.get();
        // If there are residual characters, we might need another get if the first one consumes a newline
    }

    void displayInventory() {
        UI::clearScreen();
        UI::printHeader("CURRENT STOCK INVENTORY");
        std::cout << UI::BOLD << UI::BLUE << "+------+----------------------+-------+------------+--------------------------------+" << UI::RESET << std::endl;
        std::cout << UI::BOLD << UI::BLUE << "| ID   | NAME                 | STOCK | PRICE ($)  | DESCRIPTION                    |" << UI::RESET << std::endl;
        std::cout << UI::BOLD << UI::BLUE << "+------+----------------------+-------+------------+--------------------------------+" << UI::RESET << std::endl;
        
        for (const auto& p : invMgr.getProducts()) {
            std::cout << UI::BLUE << "| " << UI::RESET;
            p->displayDetails();
        }
        
        std::cout << UI::BOLD << UI::BLUE << "+------+----------------------+-------+------------+--------------------------------+" << UI::RESET << std::endl;
        UI::printInfo("Total items: " + std::to_string(invMgr.getProducts().size()));
        std::cout << "\n  [Press Enter to return to menu]" << std::endl;
        std::cin.get();
        UI::clearScreen();
    }

    void updateStock() {
        int pID = InputValidator::getInteger("Enter Product ID: ");
        int wID = InputValidator::getInteger("Enter Warehouse ID: ");
        int qty = InputValidator::getInteger("Enter Quantity (positive to add, negative to deduct): ", -1000, 1000);
        
        if (invMgr.updateStock(pID, wID, qty)) {
            UI::printSuccess("Stock updated successfully.");
        } else {
            UI::printError("Failed to update stock. Check IDs or availability.");
        }
    }

    void processSale() {
        int pID = InputValidator::getInteger("Enter Product ID to sell: ");
        int qty = InputValidator::getInteger("Enter Quantity: ", 1, 100);
        ordProc.processSale(pID, 1, qty); // Defaulting to Warehouse 1 for demo
    }
};
