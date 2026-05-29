#include "viewport_panel.h"
#include "graphics/renderer.h"

void ViewportPanel::Draw(EditorContext& ctx)
{
    if (ImGui::Begin("Viewport")) {
        ImVec2 size = ImGui::GetContentRegionAvail();
        if (size.x < 1.0f) size.x = 1.0f;
        if (size.y < 1.0f) size.y = 1.0f;
        uint32_t w = (uint32_t)size.x;
        uint32_t h = (uint32_t)size.y;

        if (w != pendingViewportW || h != pendingViewportH) {
            pendingViewportW = w;
            pendingViewportH = h;
            viewportSizeChanged = true;
        }

        if (viewportSizeChanged && !ImGui::IsAnyItemActive()) {
            if (w > 0 && h > 0 && (w != lastViewportW || h != lastViewportH)) {
                lastViewportW = w;
                lastViewportH = h;
                ctx.renderer.RequestSceneResize(w, h);
            }
            viewportSizeChanged = false;
        }

        ImGui::Image((ImTextureID)ctx.finalTextureID, size);
    }
    ImGui::End();
}
