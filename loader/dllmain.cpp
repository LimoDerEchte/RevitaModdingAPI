
#include <Windows.h>
#include <iostream>

#include "Loader.hpp"
#include "Console/Console.hpp"

#pragma comment(linker, "/export:get_server_real_time=SteamAPIExtensionOriginal.get_server_real_time")

DWORD WINAPI OnProcessAttach(LPVOID lpParam);
DWORD WINAPI OnProcessDetach(LPVOID lpParam);

BOOL WINAPI DllMain(const HINSTANCE hInstDll, const DWORD fdwReason, const LPVOID lpReserved) { // NOLINT(*-misplaced-const)
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInstDll);
        if (const HANDLE hHandle = CreateThread(nullptr, 0, OnProcessAttach, hInstDll, 0, nullptr); hHandle != nullptr) // NOLINT(*-misplaced-const)
            CloseHandle(hHandle);
    } else if (fdwReason == DLL_PROCESS_DETACH && !lpReserved) {
        OnProcessDetach(nullptr);
    }
    return TRUE;
}

// ReSharper disable once CppDFAConstantFunctionResult
DWORD WINAPI OnProcessAttach(LPVOID) {
    Console::Alloc();
    printf_s("Revita Mod Loader Version 0.1.0\n\n");

    SetDllDirectoryA("loader");

    const HMODULE minHook = LoadLibraryA("loader/MinHook.x64.dll");
    if (minHook == nullptr) {
        printf_s("Failed to load MinHook.x64.dll!");
        return 0;
    }

    const auto mh_initialize = GetProcAddress(minHook, "MH_Initialize");
    if (mh_initialize == nullptr) {
        printf_s("Failed to get MH_Initialize!");
        return 0;
    }

    if (mh_initialize() != 0) {
        printf_s("Failed to initialize MinHook!");
        return 0;
    }
    printf_s("MinHook successfully initialized.\n");

    Loader::LoadMods("mods");
    return 0;
}

DWORD WINAPI OnProcessDetach(LPVOID) {
    return 0;
}