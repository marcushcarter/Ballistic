#include "Application.h"

#include "Layers/RenderLayer.h"

#include "Renderer/GLRenderer.h"
#include "Renderer/VkRenderer.h"

#include "Platform/GLFW/GLFWWindow.h"

namespace Ballistic {

	Application::Application(WindowProps windowProps, WindowAPI windowAPI)
		: m_WindowAPI(windowAPI) {

		switch (m_WindowAPI) {
			case WindowAPI::GLFW:
				m_Window = GLFWWindow::Create(windowProps);
				break;
		}

		RendererAPI::SetAPI(RendererAPI::API::OpenGL);

		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::OpenGL:
	            m_Renderer = std::make_unique<GLRenderer>();
	            break;
			case RendererAPI::API::Vulkan:
	            m_Renderer = std::make_unique<VkRenderer>();
	            break;
		}

		if (m_Renderer) m_Renderer->Init();

		auto renderLayer = std::make_shared<RenderLayer>(m_LayerStack, "RenderLayer");
		m_LayerStack.pushLayer(renderLayer);
		m_RenderLayer = renderLayer;
	}

	void Application::Shutdown(){
		 if (m_Renderer)
	        m_Renderer->Shutdown();
	}

	void Application::run() {
		while (!m_Window->shouldClose()) {
			m_LayerStack.onUpdate();

			m_Window->onUpdate();
		}

		Shutdown();
	}
}