#include "Platform/GLFW/GLFWWindow.h"

int main() {
    Ballistic::GLFWWindow window({"Ballistic Runtime"});

    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 0.0, 1.0, 1.0);

        window.onUpdate();
    }

    return 0;
}
