#pragma once

#ifdef _WIN32
    #include <windows.h>
    #include <shellapi.h>
#endif

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <cfloat>
#include <atomic>
#include <random>
#include <cstdint>

#include <set>
#include <cstdint>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include <stb_image.h>

#include <glad/glad.h>
#include <Platform/OpenGL/all.h>
#include <Platform/OpenGL/ShaderGLM.h>
#include <GLFW/glfw3.h>

#include <entt/entt.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>