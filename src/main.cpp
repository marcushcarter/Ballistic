#include "BEngine/engine.hpp"
#include "BEngine/engine_editor.hpp"

#include <iostream>
#include <cmath>

int main() {

    BE::Engine engine("Engine");
    BE::Editor editor(&engine);

    engine.resources().loadMesh("Test Scene", "res/models/scene.obj");

    editor.selectedAnchor = engine.activeScene->createAnchor();
    engine.activeScene->registry.transforms[editor.selectedAnchor] = BE::TransformComponent{{0,0,0}, {0,0,0}, {1,1,1}};
    engine.activeScene->registry.meshes[editor.selectedAnchor] = BE::MeshComponent{engine.resources().meshes["default_cube"], nullptr, nullptr};

    // OLD

    engine.activeScene->lights().addLight("light1", 1);
    engine.activeScene->lights().getLight("light1")->setPosition(glm::vec3(0,0.5,0));
    engine.activeScene->lights().updateGPU();

    while(engine.isRunning()) {

        engine.beginFrame();

        engine.activeScene->activeCamera->updateViewMatrix();

        engine.viewport.get()->scene = engine.activeScene;
        engine.viewport.get()->camera = engine.activeScene->activeCamera;
        engine.viewport->scene->lights().updateGPU();
        engine.renderViewportTexture(*engine.viewport.get());

        engine.viewport->scene->lights().updateGPU();

        editor.Frame();

        glfwSwapBuffers(engine.getWindow());
    }

    return 0;
}