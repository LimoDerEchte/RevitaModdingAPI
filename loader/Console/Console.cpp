
#include "Console.hpp"

#include <cstdio>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

void Console::Alloc() {
    AllocConsole();

    SetConsoleTitleA("Revita Mod Loader");

    FILE* logFile = nullptr;
    fopen_s(&logFile, "loader/latest.log", "w");
    if (logFile) {
        _dup2(_fileno(logFile), _fileno(stdout));
        _dup2(_fileno(logFile), _fileno(stderr));
    }

    freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
    freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);

    ShowWindow(GetConsoleWindow(), SW_SHOW);
}

void Console::Free() {
    fclose(stdin);
    fclose(stdout);

    FreeConsole();
}
