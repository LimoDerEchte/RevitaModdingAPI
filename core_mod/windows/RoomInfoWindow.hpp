
#pragma once

#include <YYToolkit/YYTK_Shared.hpp>

namespace RoomInfoWindow {

    inline void Draw(YYTK::YYTKInterface* yytk) {
        ImGui::Begin("Current Room Info");

        ImGui::SetWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetWindowSize(ImVec2(350, 800), ImGuiCond_Always);

        YYTK::CInstance* global;
        yytk->GetGlobalInstance(&global);

        YYTK::CRoom* room;
        yytk->GetCurrentRoomData(room);
        const YYTK::CRoomInternal internal = room->GetMembers();

        if (ImGui::CollapsingHeader("Basic Room Info", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text(room->m_Persistent ? "Persistent Room" : "Non Persistent Room");
            ImGui::Text("Room Size: %d x %d", room->m_Width, room->m_Height);
            ImGui::Spacing();
        }

        if (ImGui::CollapsingHeader("Member Information", ImGuiTreeNodeFlags_DefaultOpen)) {
            const auto instances = internal.m_ActiveInstances;
            ImGui::Text("%d Members", instances.m_Count);
            ImGui::Separator();
        }

        ImGui::End();
    }
}
