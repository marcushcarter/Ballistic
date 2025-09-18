#include "BEngine/engine.hpp"
#include "BEngine/engine_editor.hpp"

#include <iostream>
#include <cmath>

int main() {

    BE::Engine engine("Engine");
    BE::Editor editor(&engine);

    std::shared_ptr<BE::Scene> scene = std::make_shared<BE::Scene>();

    BE::Viewport vp1;
    vp1.scene = scene;
    vp1.camera = scene->cameras["Camera1"];
    vp1.resize(720, 450);

    engine.resources().loadMesh("Test Scene", "res/models/scene.obj");

    scene->lights().addLight("light1", 1);
    scene->lights().getLight("light1")->setPosition(glm::vec3(0,0.5,0));
    
    bool show_demo_window = true;

    while(engine.isRunning()) {

        engine.beginFrame();

        vp1.resize(engine.width/2, engine.height/2);
        
        if (engine.frameTime.frameCountFPS == 1) std::cout << engine.frameTime.fps << " FPS " << engine.frameTime.ms << " MS" << std::endl;

        // scene->activeCamera->handleInputs(engine.getWindow(), engine.frameTime.dt);
        scene->activeCamera->updateViewMatrix();

        if (glfwGetKey(engine.getWindow(), GLFW_KEY_0) == GLFW_PRESS) { engine.resources().recompileShaders(); }

        scene->lights().getLight("light1")->setIntensity(std::sinf(glfwGetTime()) + 1.0f);
        scene->lights().getLight("light1")->setDirection(glm::vec3(0, std::sinf(glfwGetTime()), 0));
        scene->lights().updateGPU();

        engine.renderViewportTexture(vp1);
        
        // vp1.framebuffer.bindTexture(engine.resources().shaders["__blit"]->ID, "screenTexture", 3);
        // engine.resources().meshes["__quad"]->draw(*engine.resources().shaders["__blit"], false);

        editor.beginFrame();

        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a test window!");
        ImVec2 size = ImGui::GetContentRegionAvail();
        ImGui::Image((void*)(intptr_t)vp1.framebuffer.texture, size, ImVec2(0, 1), ImVec2(1, 0));
        if (ImGui::Button("Click Me!")) {}
        ImGui::End();

        editor.showPanels();

        editor.endFrame();

        glfwSwapBuffers(engine.getWindow());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}