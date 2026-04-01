#include "Product.h"
#include "Employee.h"
#include "Stocks.h"
#include "Warehouse.h"

int main() {
    UI::printHeader("OptiTrack Inventory - Test Run");

    // Test Products
    UI::printInfo("Testing Product Display:");
    Product p1(101, "Laptop Pro", "16GB RAM, 512GB SSD", 1200.00);
    Product p2(102, "Smartphone X", "6.5inch Display, 128GB", 800.00);
    
    std::cout << std::left << std::setw(6) << "ID" 
              << std::setw(20) << "NAME" 
              << std::setw(12) << "PRICE" 
              << "DESCRIPTION" << std::endl;
    p1.displayDetails();
    p2.displayDetails();

    // Test Employee Hierarchy
    UI::printHeader("Employee Management Testing");
    Employee ceo(1, "Alice Johnson", "CEO");
    Employee mgr(2, "Bob Smith", "Warehouse Manager", &ceo);
    Employee staff(3, "Charlie Brown", "Stock Staff", &mgr);

    ceo.addSubordinate(&mgr);
    mgr.setManager(&ceo);
    mgr.addSubordinate(&staff);
    staff.setManager(&mgr);

    UI::printInfo("Company Organizational Chart:");
    ceo.displayHierarchy();

    UI::printSuccess("System core components validated!");
    return 0;
}
