# 📦 OptiTrack: Comprehensive Project Breakdown

This guide is your **Presentation Script**. It covers every file in the system and provides a line-specific walkthrough for your core source files. 🚀✨

---

## 🗂️ 1. Complete File Architecture (Summary)

### Core Logic & UI
*   `main.cpp`: The entry point that initializes the terminal environment and launches the app.
*   `MenuSystem.h`: The "Brain" of the app; handles role-based menus and routes user actions.
*   `Common.h`: Defines the UI design system (colors, box-drawing, and headers).
*   `InputValidator.h`: Ensures all user inputs are safe and correctly typed (prevents crashes).
*   `FileManager.h`: Handles low-level CSV file reading and writing operations.

### Data Management
*   `InventoryManager.h`: The central database hub; manages products and stock synchronization.
*   `OrderProcessor.h`: Handles the "Point of Sale" (POS) logic, revenue tracking, and invoicing.
*   `StaffManager.h`: Manages the HR hierarchy and employee profiles.

### Entities (The "Objects")
*   `Product.h / Product.cpp`: Defines the basic Product properties (ID, Name, Price, Stock).
*   `PerishableProduct.h`: A specialized product class that includes expiry date tracking.
*   `Order.h`: Represents a single sales transaction record.
*   `Employee.h`: Defines the properties of users (Admin, Manager, Staff).
*   `Stocks.h`: Maps a specific product to a quantity inside a specific warehouse.
*   `Warehouse.h`: Represents a physical storage location in the system.
*   `Provider.h`: Manages the relationship between suppliers and products.

---

## 🔍 2. Line-by-Line Breakdown: `main.cpp`

| Line(s) | Code / Logic Explanation |
| :--- | :--- |
| **1** | Includes `MenuSystem.h` to access the application's starting logic. |
| **3-5** | **Platform Check**: Includes `<windows.h>` specifically if running on Windows for OS-level control. |
| **7** | **main() function**: The starting point where the CPU begins execution. |
| **10** | `chcp 437`: Forces the Windows terminal to support "Extended ASCII" (Used for our UI boxes). |
| **11-12** | Gets the "handle" (reference) to the current terminal window. |
| **13-17** | **The Magic Part**: Enables "Virtual Terminal Processing". This allows our terminal to understand colors like Red and Green. |
| **22** | `MenuSystem app`: Creates the main object that holds all our database managers. |
| **25** | `app.start()`: Calls the method that shows the login screen and starts the loop. |
| **27** | Ends the program successfully. |

---

## 🔍 3. Line-by-Line Breakdown: `src/Product.cpp`

| Line(s) | Code / Logic Explanation |
| :--- | :--- |
| **1** | Includes the Header file that defines the Product class structure. |
| **3-4** | **Constructor**: Receives data (ID, Name, etc.) and uses an "initializer list" (the colon part) to efficiently set class variables. |
| **6** | `displayDetails()`: A method to print the product as a single row in a table. |
| **7-11** | **Formatted Output**: Uses `std::setw(X)` to set column widths. `std::fixed` and `setprecision(2)` ensure prices look like `$99.99` (exactly 2 decimals). |
| **14-16** | **toCSV()**: Converts the Product data into a comma-separated string for saving to a file. |
| **18** | **fromCSV()**: A "Static" function. It takes 1 line of text from a file and turns it back into a Product object. |
| **19-21** | Initializes a `stringstream` to split the text line by commas. |
| **23-25** | **The Tokenizer**: Loops through the line, finds every comma, and stores the text chunks in a `vector`. |
| **27-29** | If we successfully found at least 4 chunks, we convert them (string to int/double) and return a new Product. |
| **31** | **Safety**: Returns an "Error product" if the CSV line was corrupted or empty. |

---

## 🎤 4. Final Pitch Strategy
- **Start with "Why"**: *"We target the problem of manual inventory errors by building a role-specific terminal command center."*
- **Explain the "OOPS" Advantage**: Mention that `PerishableProduct` inherits from `Product`—this is **Inheritance** in action!
- **Highlight the "Alert System"**: Talk about how the **Low Stock Sentinel** proactively warns the manager before they run out of stock. ✨🛰️📈

---

**You are now fully briefed! Good luck with the presentation tomorrow.** 🚀📦📈
