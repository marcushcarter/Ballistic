#pragma once

#include "Core/Singleton.h"
#include "Core/Root.h"
#include "Core/IApplication.h"

#include "Core/Layers/IEvent.h"
#include "Core/Layers/Events.h"
#include "Core/Layers/ILayer.h"
#include "Core/Layers/Layerstack.h"

#include "Core/LogManager/LogManager.h"
#include "Core/LogManager/Log.h"

#include "Core/Window/WindowInfo.h"
#include "Core/Window/Window.h"

#include <stb_image.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include <imgui.h>
// #include <imgui_internal.h>
// #include <imgui_impl_opengl3.h>
// #include <imgui_impl_glfw.h>

// #include <entt/entt.hpp>

// #include <nlohmann/json.hpp>

// #include <tinyfiledialogs.h>

#include "bepch.h"