#include "GLFWWindow.h"
#include "Core/Config.h"

namespace Ballistic {

	GLFWWindow::GLFWWindow(const WindowProps& windowProps)
		: m_windowProps(windowProps) {

	    if (!glfwInit()) {
	        std::cerr << "Failed to initialize GLFW" << std::endl;
	        glfwTerminate();
	        return;
	    }

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// if (m_windowProps.customTitleBar) {
		// 	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		// }

	    m_nativeWindow = glfwCreateWindow(m_windowProps.width, m_windowProps.height, (m_windowProps.title).c_str(), nullptr, nullptr);
	    if (!m_nativeWindow) {
	        std::cerr << "Failed to create GLFW window" << std::endl;
	        glfwTerminate();
	        return;
	    }
	
		glfwMakeContextCurrent(m_nativeWindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize OpenGL context with glad" << std::endl;
			glfwDestroyWindow(m_nativeWindow);
			glfwTerminate();
			return;
		}

		glfwSwapInterval(m_windowProps.vsync);
	}

	GLFWWindow::~GLFWWindow() {
		if (m_nativeWindow) glfwDestroyWindow(m_nativeWindow);
	}

	void GLFWWindow::OnUpdate() {
		glfwGetWindowSize(m_nativeWindow, &m_windowProps.width, &m_windowProps.height);
		glfwPollEvents();
		glfwSwapBuffers(m_nativeWindow);
	}

	bool GLFWWindow::ShouldClose() const {
		return glfwWindowShouldClose(m_nativeWindow);
	}

	void GLFWWindow::ToggleFullscreen(bool fullscreen) {
		if (fullscreen == IsFullscreen()) return;

	    if (fullscreen) {
	        glfwGetWindowPos(m_nativeWindow, &m_WindowedX, &m_WindowedY);
	        glfwGetWindowSize(m_nativeWindow, &m_WindowedW, &m_WindowedH);

	        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	        glfwSetWindowMonitor(m_nativeWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	    } else {
	        glfwSetWindowMonitor(m_nativeWindow, nullptr, m_WindowedX, m_WindowedY, m_WindowedW, m_WindowedH, 0);
	    }
	}

	bool GLFWWindow::IsFullscreen() const {
		return glfwGetWindowMonitor(m_nativeWindow) != nullptr;
	}

	std::shared_ptr<IWindow> GLFWWindow::Create(const WindowProps& windowProps) {
		return std::make_shared<GLFWWindow>(windowProps);
	}
}