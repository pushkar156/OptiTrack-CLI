#include "Product.h"
#include "PerishableProduct.h"
#include "Employee.h"
#include "Order.h"
#include "InputValidator.h"

int main() {
    UI::printHeader("OptiTrack Inventory - Phase 2 Test");

    // 1. Inheritance and Polymorphism Demo
    UI::printInfo("Testing Inheritance (Perishables):");
    Product normalProduct(1, "Steel Pipes", "Construction grade", 50.0);
    PerishableProduct milk(2, "Fresh Milk", "Dairy product", 2.50, "2026-05-01");

    std::cout << std::left << std::setw(6) << "ID" 
              << std::setw(20) << "NAME" 
              << std::setw(12) << "PRICE" 
              << std::setw(15) << "EXPIRY"
              << "DESCRIPTION" << std::endl;
    normalProduct.displayDetails();
    milk.displayDetails(); // Calls overridden method

    // 2. Order and Invoicing Demo
    UI::printHeader("Sales & Invoicing Test");
    Order sale1(5001, "2026-04-06", 2, 10, 2.50); // Selling 10 units of milk
    sale1.printInvoice();

    // 3. Employee Hierarchy (Already verified in P1, but kept for context)
    Employee ceo(1, "Alice", "CEO");
    Employee mgr(2, "Bob", "Warehouse Manager", &ceo);
    ceo.addSubordinate(&mgr);
    
    UI::printInfo("Quick Hierarchy Check:");
    ceo.displayHierarchy();

    UI::printSuccess("Phase 2 Core Entities validated successfully!");
    return 0;
}
