#pragma once

#include "bepch.h"

namespace Ballistic {

	struct WindowProps {
		std::string title;
		int width;
		int height;
		bool VSync;

		WindowProps(const std::string& title = "BallisticEngine", int width = 1280, int height = 720, bool VSync = false)
			: title(title), width(width), height(height), VSync(VSync) {}
	};
	
	class GLFWWindow {
	public:
		GLFWWindow(const WindowProps& windowProps);
		~GLFWWindow();

		void onUpdate();
		bool shouldClose() const;

		// void createVulkanSurface(VkInstance instance);

		GLFWwindow* get() const { return m_NativeWindow; }
		VkSurfaceKHR getVkSurface() const { return m_Surface; }
		WindowProps getProps() const { return m_Props; }

		void createVulkanSurface(VkInstance instance);

		static std::shared_ptr<GLFWWindow> CreateWindow(const WindowProps& windowProps = {});

	private:
		GLFWwindow* m_NativeWindow;
		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		WindowProps m_Props;
	};

}