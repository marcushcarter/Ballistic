#include <game/game_application.h>
#include <imgui.h>
#include <windows.h>
#include <shellapi.h>

namespace ballistic {

Error GameApplication::on_init() { return Error::Ok; }

void GameApplication::on_update(float p_dt)
{
    (void)p_dt;
    renderer.set_size(window.width, window.height);

#if BALLISTIC_DEV_TOOLS
    draw_menu_bar();

    dev_systems.renderbuffer_xray.draw();
#endif
}

void GameApplication::on_shutdown() {}

void GameApplication::draw_menu_bar()
{
    if (debug_menu_visible && ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools")) {

            //Mouse tools
            // -----------
            // AI >
            // Animations >
            // sequence >
            // scirpts >
            // rendergraph >
            // network >
            // quest >
            // world enumerators >
            // -----------
            // save settings
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Renderer")) {

            // wireframe
            // grid >
            //
            // -----------
            // make swatch screenshot
            // 4x mode
            // -----------
            // reverse depth
            // -----------
            if (ImGui::MenuItem("Add RenderBuffer XRay")) dev_systems.renderbuffer_xray.open = true;
            // material reference colors
            // frame sync
            // -----------
            // scenegraph >
            // lens flares > 
            // renderpasses >
            // anise debugging >
            // post debugging >
            // ambient lighting >
            // reflections and cubemaps >
            // aa filtering >
            // debug display >
            // clous rendering >
            // lighting >
            // draw debugging >
            // streaming >>
            // content instancing >
            // -----------
            // hotload shaders (CTRL+H)
            
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Performance")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Effects")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Weather")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Pie Menu")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Sound")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("HUD")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Menu")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Placement")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("Open Documentation")) {
                ShellExecuteA(nullptr, "open", "https://ballisticgames.ca", nullptr, nullptr, SW_SHOWNORMAL);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

}