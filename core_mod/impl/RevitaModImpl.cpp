
#include "imgui_internal.h"
#include "RevitaCoreGlobals.hpp"
#include "include/RevitaMod.hpp"

class RevitaModImpl final : public IRevitaMod {
public:
    ~RevitaModImpl() override = default;

    void RegisterWindow(ImGuiRenderedWindow *window) override {
        RevitaCoreMod::windows.push_back(window);
    }

    void UnregisterWindow(ImGuiRenderedWindow *window) override {
        std::erase(RevitaCoreMod::windows, window);
    }

    ImGuiContext* GetImGuiContext() override {
        return ImGui::GetCurrentContext();
    }
};

extern "C" __declspec(dllexport) IRevitaMod* core_mod_get_interface() {
    static RevitaModImpl impl;
    return &impl;
}
