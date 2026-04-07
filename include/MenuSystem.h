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
            std::cout << UI::BOLD << UI::BLUE << "  ____        _   _ _______                     \n"
                      << " / __ \\      | | (_)__   __|                    \n"
                      << "| |  | |_ __ | |_ _   | |_ __ __ _  ___ | | __  \n"
                      << "| |  | | '_ \\| __| |  | | '__/ _` |/ __|| |/ /  \n"
                      << "| |__| | |_) | |_| |  | | | | (_| | (__ |   <   \n"
                      << " \\____/| .__/ \\__|_|  |_|_|  \\__,_|\\___||_|\\_\\ \n"
                      << "       | |                                      \n"
                      << "       |_|                                      " << UI::RESET << std::endl;

            UI::printBox("CHOOSE YOUR SECURE ACCESS ROLE");
            std::cout << UI::BOLD << "  [1] " << UI::RESET << "Admin Login" << std::endl;
            std::cout << UI::BOLD << "  [2] " << UI::RESET << "Warehouse Manager" << std::endl;
            std::cout << UI::BOLD << "  [3] " << UI::RESET << "Sales Staff" << std::endl;
            std::cout << UI::BOLD << "  [0] " << UI::RESET << UI::RED << "Exit System" << UI::RESET << std::endl;

            int choice = InputValidator::getInteger("\n  Enter ID: ", 0, 3);
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
            UI::printHeader(currentRole + " Main Menu");
            UI::printBox("ACTIVE SECTIONS");
            std::cout << UI::BOLD << "  1. " << UI::RESET << "View Stock Inventory" << std::endl;
            
            // RBAC logic for menu options
            if (currentRole == "Admin" || currentRole == "Warehouse Manager") {
                std::cout << UI::BOLD << "  2. " << UI::RESET << "Restock / Update Levels" << std::endl;
            }
            if (currentRole == "Admin") {
                std::cout << UI::BOLD << "  3. " << UI::RESET << "HR: Management Hierarchy" << std::endl;
                std::cout << UI::BOLD << "  4. " << UI::RESET << "Supply Chain: Providers" << std::endl;
            }
            if (currentRole == "Admin" || currentRole == "Sales Staff") {
                std::cout << UI::BOLD << "  5. " << UI::RESET << "Create POS Transaction (Order)" << std::endl;
            }

            std::cout << UI::BOLD << "  0. " << UI::RESET << UI::RED << "Logout Session" << UI::RESET << std::endl;

            int choice = InputValidator::getInteger("\n  Select Menu Action: ", 0, 5);
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
                if (currentRole == "Admin") staffMgr.displayAll();
                else UI::printError("Access restricted to Admins only!");
                pause();
                break;
            case 5:
                processSale();
                pause();
                break;
            default:
                UI::printInfo("Feature coming soon in full release!");
                pause();
        }
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
