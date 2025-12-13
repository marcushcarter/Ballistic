#include "EditorLayer.h"

#include <imgui.h>
#include <imgui_impl_vulkan.h>
#include <imgui_impl_glfw.h>

#include "Platform/Vulkan/VulkanCommandBuffer.h"

namespace Ballistic {

	void EditorLayer::onAttach() {
	}

	void EditorLayer::onDetach() {
	}

	void EditorLayer::onUpdate() {
	}

	void EditorLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}