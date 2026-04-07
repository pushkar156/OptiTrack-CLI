#include "MenuSystem.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // 0. Initialize Windows Terminal for Colors and Clean Input
#ifdef _WIN32
    std::system("chcp 437 > nul");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif

    // 1. Initialize the UI System
    MenuSystem app;

    // 2. Start the Secure Terminal
    app.start();

    return 0;
}
