#include <core/dev_tools/xray.h>
#include <imgui.h>
#include <cstdint>

namespace ballistic {

void Xray::draw()
{
    if (!open) return;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    bool visible = ImGui::Begin("Xray", &open);
    ImGui::PopStyleVar();

    if (visible) {
        
        ImVec2 size = ImGui::GetContentRegionAvail();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        if (size.x < 1.0f) size.x = 1.0f;
        if (size.y < 1.0f) size.y = 1.0f;
        // uint32_t w = (uint32_t)size.x;
        // uint32_t h = (uint32_t)size.y;

        if (false) {
            // ImGui::Image((ImTextureID)ctx.finalTextureID, size);
        } else {
            ImDrawList* dl = ImGui::GetWindowDrawList();
            dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(255, 255, 255, 255));
        }
    }
    ImGui::End();
}

}