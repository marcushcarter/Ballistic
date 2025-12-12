#include "GLFWWindow.h"

namespace Ballistic {

	GLFWWindow::GLFWWindow(const WindowProps& windowProps)
		: m_Props(windowProps) {

	    if (!glfwInit()) {
	        std::cerr << "Failed to initialize GLFW" << std::endl;
	        glfwTerminate();
	    }

	    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	    m_NativeWindow = glfwCreateWindow(windowProps.width, windowProps.height, (windowProps.title).c_str(), nullptr, nullptr);
	    if (!m_NativeWindow) {
	        std::cerr << "Failed to create GLFW window" << std::endl;
	        glfwDestroyWindow(m_NativeWindow);
	        glfwTerminate();
	    }
	}

	GLFWWindow::~GLFWWindow() {
		if (m_NativeWindow) glfwDestroyWindow(m_NativeWindow);
		glfwTerminate();
	}

	void GLFWWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_NativeWindow);
	}

	bool GLFWWindow::shouldClose() const {
		return glfwWindowShouldClose(m_NativeWindow);
	}

	void GLFWWindow::createVulkanSurface(VkInstance instance) {
	    if (glfwCreateWindowSurface(instance, m_NativeWindow, nullptr, &m_Surface) != VK_SUCCESS) {
	        throw std::runtime_error("Failed to create Vulkan surface");
	    }
	}

	std::shared_ptr<GLFWWindow> GLFWWindow::CreateWindow(const WindowProps& windowProps) {
		return std::make_shared<GLFWWindow>(windowProps);
	}
}