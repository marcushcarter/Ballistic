#include <game/game_application.h>
#include <imgui.h>

namespace ballistic {

Error GameApplication::on_init() { return Error::Ok; }

void GameApplication::on_update(float p_dt)
{
    (void)p_dt;

#if BALLISTIC_DEV_TOOLS
    if (debug_menu_visible && ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Debug")) {
            ImGui::MenuItem("Xray", nullptr, &dev_systems.xray.open);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    dev_systems.xray.draw();
#endif

    renderer.set_size(window.width, window.height);
    // BALLISTIC_ERR_FAIL_COND_V(err != Error::Ok, );
}

void GameApplication::on_shutdown() {}
    
}