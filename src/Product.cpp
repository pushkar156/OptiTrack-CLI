#include "Product.h"

Product::Product(int id, std::string name, std::string description, double price) 
: id(id), pname(name), descrip(description), price(price) {}

void Product::displayDetails() const {
    std::cout << std::left << std::setw(6) << id 
              << std::setw(20) << pname 
              << std::setw(12) << std::fixed << std::setprecision(2) << price 
              << descrip << std::endl;
}

std::string Product::toCSV() const {
    return std::to_string(id) + "," + pname + "," + descrip + "," + std::to_string(price);
}

Product Product::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, item, ',')) {
        tokens.push_back(item);
    }
    
    if (tokens.size() >= 4) {
        return Product(std::stoi(tokens[0]), tokens[1], tokens[2], std::stod(tokens[3]));
    }
    
    return Product(0, "Error", "Error", 0.0);
}
