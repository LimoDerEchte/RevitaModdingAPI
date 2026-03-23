
#include <Aurie/shared.hpp>
#include <RevitaMod.hpp>
#include <RevitaWindow.hpp>

#include "imgui.h"

class TestWindow final : public ImGuiRenderedWindow {
    void Render() override {
        if (ImGui::GetCurrentContext() == nullptr)
            return;

        ImGui::Begin("Test Window");
        ImGui::Text("Test Window");
        ImGui::Button("Idk");
        ImGui::End();
    }
};

EXPORTED Aurie::AurieStatus ModuleInitialize(IN Aurie::AurieModule*, IN const std::filesystem::path&) {
    IRevitaMod* core = IRevitaMod::GetInterface();
    if (!core)
        return Aurie::AURIE_MODULE_DEPENDENCY_NOT_RESOLVED;

    ImGui::SetCurrentContext(core->GetImGuiContext());

    TestWindow window;
    core->RegisterWindow(&window);

    return Aurie::AURIE_SUCCESS;
}
