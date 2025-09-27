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

        engine.viewport.get()->scene = engine.activeScene;
        engine.viewport.get()->camera = engine.activeScene->activeCamera;
        engine.renderViewportTexture(*engine.viewport.get());

        editor.Frame();

        glfwSwapBuffers(engine.getWindow());
    }

    return 0;
}
