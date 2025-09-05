#include "include/engine.hpp"

#include <iostream>

int main() {

    BE_Engine engine("My Engine");
    engine.bind();

    BE_VAO vao;

    while(engine.isRunning()) {
        engine.beginFrame();

        engine.beginRender();
        engine.endFrame();
    }

    engine.~BE_Engine();
    return 0;
}