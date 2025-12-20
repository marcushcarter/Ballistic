#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
    #include <shellapi.h>
#endif

#include <algorithm>
#include <atomic>
#include <cfloat>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <entt/entt.hpp>

#include <nlohmann/json.hpp>

#include <Platform/API/OpenGL/all.h>
#include <Platform/API/OpenGL/ShaderGLM.h>

#include <Core/Utils.h>