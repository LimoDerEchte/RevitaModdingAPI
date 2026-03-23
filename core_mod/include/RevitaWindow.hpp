
#pragma once

#include "imgui_internal.h"

struct ImGuiRenderedWindow {
    virtual ~ImGuiRenderedWindow();
    virtual void Render();

    void RenderInternal(ImGuiContext* ctx) {
        ImGui::SetCurrentContext(ctx);
        Render();
    }
};
