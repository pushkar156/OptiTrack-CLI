#include "Product.h"

Product::Product(int id, std::string name, std::string description, double price, int stock) 
: id(id), pname(name), descrip(description), price(price), stockCount(stock) {}

void Product::displayDetails() const {
    std::cout << std::left << std::setw(5) << id << "| " 
              << std::setw(21) << pname << "| " 
              << std::setw(7) << stockCount << "| " 
              << std::setw(10) << std::fixed << std::setprecision(2) << price << "| " 
              << std::setw(30) << descrip << " |" << std::endl;
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
