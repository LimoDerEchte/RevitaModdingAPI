
#pragma once

struct ImGuiRenderedWindow {
    virtual ~ImGuiRenderedWindow() = default;
    virtual void Render() = 0;
};
