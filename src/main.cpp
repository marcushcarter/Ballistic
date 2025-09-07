#include "include/engine.hpp"
#include "engine_default.hpp"

#include <iostream>

const std::string vertexSrc = R"(
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec2 aTex;

uniform mat4 uMVP;

out vec2 TexCoord;

void main() {
    gl_Position = uMVP * vec4(aPos, 1.0);
    TexCoord = aTex;
}
)";

const std::string fragmentSrc = R"(
#version 460 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D diffuse0;

void main() {
    FragColor = texture(diffuse0, TexCoord);
}
)";

int main() {

    BE_Engine engine("Test Cube");
    engine.bind();

    // BE_Texture texture1("box diffuse", "res/textures/box.png", "diffuse", 0);
    // BE_Texture texture2("box specular", "res/textures/box_specular.png", "specular", 1);
    // std::vector<BE_Texture> textures = { texture1, texture2 };

    BE_Mesh cube("Cube", {}, {}, {});
    cube.loadOBJ("res/models/scene.obj");

    BE_Texture texture1("fallback", "diffuse", 2, 2, BE::Default::fallbackTexture);

    BE_Shader shader("CubeShader", &vertexSrc, &fragmentSrc);
    BE_Camera camera("MainCam", engine.width, engine.height, 45.0f, 0.1f, 100.0f, {0,0,3}, {0,0,-1});
    glfwSwapInterval(0);

    while(engine.isRunning()) {

        engine.beginFrame();
        
        if (engine.frameTime.frameCountFPS == 1) std::cout << engine.frameTime.fps << " FPS " << engine.frameTime.ms << " MS" << std::endl;

        camera.handleInputs(engine.window, engine.frameTime.dt);
        camera.updateViewMatrix();

        // updates

        engine.beginRender();

        glm::mat4 model = glm::mat4(1.0f);
        camera.uploadToShader(shader.ID, model);
        cube.draw(shader);

        engine.endFrame();
    }

    engine.~BE_Engine();
    return 0;
}