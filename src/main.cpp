#include "BEngine/engine.hpp"
#include "BEngine/engine_editor.hpp"

#include <iostream>
#include <cmath>

int main() {

    BE::Engine engine("Engine");
    BE::Editor editor(&engine);

    while(engine.isRunning()) {

        engine.beginFrame();

        engine.activeScene->activeCamera->updateViewMatrix();
        
        engine.viewport->scene = engine.activeScene;
        engine.viewport->camera = engine.activeScene->activeCamera;
        engine.render();

        editor.Frame();

        glfwSwapBuffers(engine.getWindow());
    }

    return 0;
}
