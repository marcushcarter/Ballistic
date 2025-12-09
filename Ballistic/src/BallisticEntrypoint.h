#pragma once

#include "Core/application.h"

int main(int argc, char** argv) {
    Ballistic::Application* app = new Ballistic::Application();
    app->run();
    // delete app;
}