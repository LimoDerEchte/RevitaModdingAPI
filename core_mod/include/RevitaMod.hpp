
#pragma once

#include <Windows.h>
#include <imgui.h>

#include "RevitaWindow.hpp"

struct IRevitaMod;
typedef IRevitaMod*(*get_interface_f)();

struct IRevitaMod {
    virtual ~IRevitaMod() = default;

    virtual void RegisterWindow(ImGuiRenderedWindow* window);
    virtual void UnregisterWindow(ImGuiRenderedWindow* window);
    virtual ImGuiContext* GetImGuiContext();

    static IRevitaMod* GetInterface() {
        static IRevitaMod* instance = nullptr;
        if (!instance) {
            const HMODULE hModule = GetModuleHandle("RevitaCoreMod.dll");
            if (!hModule)
                return nullptr;
            const auto func = reinterpret_cast<get_interface_f>(GetProcAddress(hModule, "core_mod_get_interface"));
            if (!func)
                return nullptr;
            instance = func();
        }
        return instance;
    }
};
