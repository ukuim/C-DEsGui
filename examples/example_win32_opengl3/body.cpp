#include "body.h"
#include <imgui.h>
void show_query_window_ui() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.98f, 0.76f, 0.92f, 1.0f));
   ImGui::SetNextWindowSize(ImVec2(640, 400));
    ImGui::Begin("##œ‘ æ", &show_query_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    ImGui::PopStyleVar(2);
   
    ImGui::Text(u8"ƒ„∫√");


    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 50, ImGui::GetWindowSize().y - 30));

    if (ImGui::Button(u8"πÿ±’")) {
        show_query_window = false; 
    }


    ImGui::PopStyleColor();
  


    ImGui::End();
}
