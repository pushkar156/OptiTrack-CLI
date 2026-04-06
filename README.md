# OptiTrack: Inventory Control System

**OptiTrack** is a high-performance, object-oriented Inventory Control System developed in **C++** to manage organizational logistics and warehouse operations. It uses a modular class hierarchy to model real-world business entities.

## 🚀 Key Features

-   **Modular Architecture**: Entities like `Products`, `Providers`, `Stocks`, and `Warehouses` are encapsulated modular classes.
-   **Hierarchical Management**: Automatic **Management Tree Reconstruction** from CSV data using self-referential pointers.
-   **Data Persistence**: Integrated **FileManager** for automatic saving/loading of application state to `.csv` format.
-   **Role-Based Access Control (RBAC)**:
    -   **Admin**: Full system access, HR management, and supplier configuration.
    -   **Warehouse Manager**: Focused on stock levels and allocation logic.
    -   **Sales Staff**: Restricted access for processing orders and inventory viewing.
-   **Premium CLI UI**: Standard ASCII table-based grid layouts, ANSI color-coding, and screen-clearing navigation.

## 🛠️ OOPS Pillars Applied

-   **Encapsulation**: Private data members protected via public interfaces.
-   **Inheritance**: `PerishableProduct` inherits from `Product` to handle expiration logic.
-   **Polymorphism**: Overridden `displayDetails()` methods for uniform object treatment.
-   **Abstraction**: Utility managers (`InventoryManager`, `StaffManager`) abstract complex logic from the UI.
-   **Smart Memory**: Extensive use of `std::unique_ptr` for automatic object lifecycle management.

## 📁 Project Structure

```text
OptiTrack/
├── include/           # Header files (.h)
│   ├── Common.h       # UI Utils & ANSI Colors
│   ├── FileManager.h  # File I/O Logic
│   ├── InventoryManager.h # Business Logic Layer
│   ├── Product.h / PerishableProduct.h  # Entity Classes
│   ├── Employee.h / StaffManager.h # Hierarchy Logic
│   └── OrderProcessor.h # Sales Workflow
├── src/               # Implementation files (.cpp) 
│   └── Product.cpp
├── data/              # Persistent CSV records
├── CMakeLists.txt     # Cross-platform build script
└── main.cpp           # Interactive CLI Entry Point
```

## ⚙️ Building the Project

### Using G++ (Recommended)
Compile the project with C++14 support or higher:
```bash
g++ main.cpp src/Product.cpp -I include -o OptiTrack -std=c++14
```

### Run the Application
```bash
./OptiTrack
```

## 🧪 Testing and Results
-   **Persistence**: Data for **Pushkar (CEO)** and core products is automatically saved to disk.
-   **Validation**: The `InputValidator` handles all invalid keystrokes to prevent program crashes.
-   **Traceability**: Professional **Invoices** are generated with unique IDs for every transaction.

---
*Created as part of the OOPS Lab Project - Second Year B.Tech.*
