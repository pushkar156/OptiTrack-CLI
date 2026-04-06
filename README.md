# 📦 OptiTrack: Inventory Control System

![C++ Version](https://img.shields.io/badge/C%2B%2B-14%2B-blue.svg)
![Build](https://img.shields.io/badge/Build-CMake-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-orange.svg)
![License](https://img.shields.io/badge/License-MIT-purple.svg)

**OptiTrack** is a high-performance, object-oriented Inventory Control System designed for modern warehouse management. By leveraging **Self-Referential Hierarchies** and **Polymorphic Entities**, it provides a robust platform for tracking stock, managing large teams, and processing transactions with high integrity.

---

## ✨ Premium UI Experience

Our system features a **Command-Line Interface (CLI)** designed for readability and professional focus:
- **Box-Model Frames**: Structured menus and interactive prompts.
- **ASCII Grid Tables**: Perfectly aligned inventory listings.
- **Color-Coded Status**: 
  - `[OK]` (Green): Successful operations.
  - `[!]`  (Red): Permission denied or errors.
  - `[i]`  (Yellow): System information/logs.

---

## 🚦 Role-Based Access Control (RBAC)

To ensure security across the organization, access is strictly managed via roles:

| Role | Access Level | Description |
| :--- | :--- | :--- |
| **🛡️ Admin** | `Superuser` | Full CRUD on inventory, HR management, and supplier links. |
| **🏢 Wh. Manager** | `Strategic` | Stock level updates, restocks, and warehouse allocation. |
| **💼 Sales Staff** | `Operational` | View stock availability and process new POS transactions. |

---

## 🏗️ Architectural Foundations (OOPS)

This project demonstrates the core pillars of Object-Oriented Programming:

1. **Encapsulation**: Attributes like `unitPrice` and `stockCount` are private, protected by rigorous validation logic in public methods.
2. **Inheritance**: The `PerishableProduct` class extends the base `Product` class, adding expiration tracking and specialized display logic.
3. **Polymorphism**: The `displayDetails()` method is overridden across the product hierarchy, allowing for unified inventory rendering.
4. **Abstraction**: Dedicated `Manager` classes handle the complexity of file I/O and data reconstruction, providing a clean API for the UI.
5. **Smart Persistence**: Automatic CSV serialization ensures that your organizational state is preserved across reboots.

---

## 📂 Project Structure

```text
OptiTrack/
├── include/           # Comprehensive Header Files (.h)
│   ├── Common.h       # UI Utilities & ANSI Colors
│   ├── Employee.h     # Hierarchical Employee Entity (OOPS Inheritance)
│   ├── FileManager.h  # Robust File I/O Serialization
│   ├── InputValidator.h # User Input Sanitization Logic
│   ├── InventoryManager.h # High-Level Stock Management
│   ├── MenuSystem.h   # Core Application CLI Framework
│   ├── Order.h        # Transaction Data Model
│   ├── OrderProcessor.h # Sales & Invoicing Workflow
│   ├── PerishableProduct.h # Specialized Product Subtype (Inheritance)
│   ├── Product.h      # Base Product Class
│   ├── Provider.h     # Supplier Tracking Entity
│   ├── StaffManager.h # Management Tree Logic
│   ├── Stocks.h       # Inventory Location Hub
│   └── Warehouse.h    # Storage Facility Model
├── src/               # Implementation Layer (.cpp) 
│   └── Product.cpp    # Core Entity Methods
├── data/              # Fully Synchronized CSV Storage
├── CMakeLists.txt     # Cross-platform Build Configuration
└── main.cpp           # Interactive CLI Entry Point
```

---

## ⚙️ Quick Start Guide

### 1. Requirements
Ensure you have a C++ compiler supporting at least **C++14** (GCC 4.9+ or MSVC 17.0+).

### 2. Compilation
```bash
g++ main.cpp src/Product.cpp -I include -o OptiTrack -std=c++14
```

### 3. Usage Walkthrough
1. **Login**: Launch the app and select **[1] Admin Login**.
2. **Setup HR**: Check section **[3] Management Hierarchy** to see your team's tree.
3. **Inventory Check**: View current stock in section **[1]**.
4. **Process a Sale**: Select **[5] Create POS Transaction**. The system automatically:
   - Validates stock availability.
   - Updates `Stocks.csv` in real-time.
   - Generates a custom **POS Invoice**.
   - Logs the transaction in `Orders.csv`.

---

## 🧪 Testing and Verification
- **Stress Tested**: Handles 100+ items and deep organizational trees (5+ levels).
- **Crash Proof**: Ruggedized with `InputValidator` to ignore invalid terminal input.
- **Memory Safe**: Utilizes `std::unique_ptr` for automated resource cleanup.

---
*Developed for the OOPS Laboratory Project - Second Year B.Tech.*  
**Author: Pushkar & The Team**
