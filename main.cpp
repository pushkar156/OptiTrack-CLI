#include "MenuSystem.h"

int main() {
    // 0. Force Standard ASCII Code Page for Windows
#ifdef _WIN32
    std::system("chcp 437 > nul");
#endif

    // 1. Initialize the UI System
    MenuSystem app;

    // 2. Start the Role-Based Main Controller
    try {
        app.start();
    } catch (const std::exception& e) {
        UI::printError("Application Error: " + std::string(e.what()));
    }

    // 3. Graceful Exit
    UI::printHeader("THANK YOU FOR USING OPTITRACK!");
    return 0;
}
