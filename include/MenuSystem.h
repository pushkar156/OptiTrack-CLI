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
            UI::printHeader("OPTITRACK INVENTORY CONTROL SYSTEM");
            std::cout << "1. Login as Admin" << std::endl;
            std::cout << "2. Login as Warehouse Manager" << std::endl;
            std::cout << "3. Login as Sales Staff" << std::endl;
            std::cout << "0. Exit" << std::endl;

            int choice = InputValidator::getInteger("\nSelect Role: ", 0, 3);
            if (choice == 0) break;

            if (choice == 1) login("Admin");
            else if (choice == 2) login("Warehouse Manager");
            else if (choice == 3) login("Sales Staff");
        }
    }

private:
    void login(std::string role) {
        currentRole = role;
        UI::printHeader("LOGGED IN AS: " + role);
        showMainMenu();
    }

    void showMainMenu() {
        while (true) {
            UI::printHeader(currentRole + " Main Menu");
            std::cout << "1. View Inventory" << std::endl;
            
            // RBAC logic for menu options
            if (currentRole == "Admin" || currentRole == "Warehouse Manager") {
                std::cout << "2. Update Stock Levels" << std::endl;
            }
            if (currentRole == "Admin") {
                std::cout << "3. Manage Employees" << std::endl;
                std::cout << "4. Configure Suppliers (Providers)" << std::endl;
            }
            if (currentRole == "Admin" || currentRole == "Sales Staff") {
                std::cout << "5. Process New Sale (Order)" << std::endl;
            }

            std::cout << "0. Logout" << std::endl;

            int choice = InputValidator::getInteger("\nEnter Action: ", 0, 5);
            if (choice == 0) break;

            handleAction(choice);
        }
    }

    void handleAction(int choice) {
        switch (choice) {
            case 1:
                displayInventory();
                break;
            case 2:
                if (currentRole != "Sales Staff") updateStock();
                else UI::printError("Access Denied for Sales Staff!");
                break;
            case 3:
                if (currentRole == "Admin") staffMgr.displayAll();
                else UI::printError("Access restricted to Admins only!");
                break;
            case 5:
                processSale();
                break;
            default:
                UI::printInfo("Feature coming soon in full release!");
        }
    }

    void displayInventory() {
        UI::printHeader("CURRENT STOCK INVENTORY");
        std::cout << std::left << std::setw(6) << "ID" 
                  << std::setw(20) << "NAME" 
                  << std::setw(12) << "PRICE" 
                  << "DESCRIPTION" << std::endl;
        for (const auto& p : invMgr.getProducts()) {
            p->displayDetails();
        }
        std::cout << "\n[Press Enter to continue]" << std::endl;
        std::cin.get();
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
