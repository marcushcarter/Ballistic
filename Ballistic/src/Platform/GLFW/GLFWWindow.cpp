#include "GLFWWindow.h"

namespace Ballistic {

	GLFWWindow::GLFWWindow(RendererAPI rendererAPI, const WindowProps& windowProps)
		: m_Props(windowProps) {

	    if (!glfwInit()) {
	        std::cerr << "Failed to initialize GLFW" << std::endl;
	        glfwTerminate();
	        return;
	    }

	    switch (rendererAPI) {
	        case RendererAPI::OpenGL:
	            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	            break;
	        case RendererAPI::Vulkan:
	            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	            break;
	        default:
	            std::cerr << "Unsupported RendererAPI" << std::endl;
	            glfwTerminate();
	            return;
   		}

	    m_NativeWindow = glfwCreateWindow(windowProps.width, windowProps.height, (windowProps.title).c_str(), nullptr, nullptr);
	    if (!m_NativeWindow) {
	        std::cerr << "Failed to create GLFW window" << std::endl;
	        glfwTerminate();
	        return;
	    }

	    if (rendererAPI == RendererAPI::OpenGL) {
	        glfwMakeContextCurrent(m_NativeWindow);
	        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	            std::cerr << "Failed to initialize OpenGL context with glad" << std::endl;
	            glfwDestroyWindow(m_NativeWindow);
	            glfwTerminate();
	            return;
	        }
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

	std::shared_ptr<IWindow> GLFWWindow::Create(RendererAPI api, const WindowProps& windowProps) {
		return std::make_shared<GLFWWindow>(api, windowProps);
	}
}