# OptiTrack : Inventory Control System

**OptiTrack** is a high-performance, object-oriented Inventory Control System developed in **C++** to manage organizational logistics and warehouse operations. It leverages core OOPS concepts to model real-world business entities as modular, reusable components.

## 🚀 Key Features

-   **Modular Architecture**: Entities like `Products`, `Providers`, `Stocks`, and `Warehouses` are represented as modular classes.
-   **Hierarchical Management**: Utilizes **self-referential pointers** in the `Employee` class to model organizational structures (Managers & Subordinates).
-   **Data Persistence**: Object states are saved to and loaded from `.csv` files using standard File I/O.
-   **Role-Based Access Control**:
    -   **Admin**: Full CRUD access and employee management.
    -   **Warehouse Manager**: Stock updates and space allocation.
    -   **Sales Staff**: Order processing and stock checking.
-   **Premium CLI Experience**: Color-coded terminal interface with robust input validation.

## 🛠️ OOPS Pillars Applied

-   **Encapsulation**: Private data members (like `price`, `stockCount`) modified only through validated public member functions.
-   **Inheritance**: Base `Product` class with extensible derived types (e.g., `PerishableProduct`).
-   **Polymorphism**: Virtual functions (e.g., `displayDetails()`) for uniform object management.
-   **Abstraction**: Abstract interfaces for core operations, hiding complex backend serialization logic.

## 📁 Project Structure

```text
OptiTrack/
├── include/           # Header files (.h)
│   ├── Common.h       # UI Utils & Standard Includes
│   ├── Product.h      # Core Product Entity
│   ├── Employee.h     # Hierarchical Employee Entity
│   └── Stocks.h       # Inventory Tracking
├── src/               # Implementation files (.cpp)
│   └── Product.cpp
├── data/              # Persistent CSV storage
├── CMakeLists.txt     # Build configuration
└── main.cpp           # Entry point / Test Controller
```

## ⚙️ Building the Project

### Prerequisites
-   **Compiler**: GCC (MinGW) or MSVC 17.0+
-   **Build Tool**: CMake 3.10+ (Recommended)

### Using CMake
1.  Navigate to the project root.
2.  Run the following commands:
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

### Using G++ (Direct)
Alternatively, you can compile the core files directly:
```bash
g++ main.cpp src/Product.cpp -I include -o OptiTrack
```

## 🧪 Testing and Results
-   **Constraint Validation**: Ensures negative prices/stocks are rejected.
-   **Recursive Check**: Displays multi-level management hierarchies without loops.
-   **Persistence Check**: Verified data retention between program sessions.

---
*Created as part of the OOPS Lab Project - Second Year B.Tech.*
