#include "Application.h"

#include "Layers/LayerStack.h"
#include "Layers/RenderLayer.h"
#include "Project/ProjectManager.h"

namespace Ballistic {

	Application::Application() {
		m_Window = Window::createWindow();

		m_LayerStack = std::make_shared<LayerStack>();
		m_ProjectManager = std::make_shared<ProjectManager>();

		m_RenderLayer = std::make_shared<RenderLayer>(m_LayerStack, m_ProjectManager);
		m_LayerStack->PushLayer(m_RenderLayer);
	}

	void Application::run() {

		while (!m_Window->shouldClose()) {

			float dt = 0.016f;

	    	m_LayerStack->OnUpdate();

			m_Window->onUpdate();
		}
	}

	void Application::Shutdown() {}

};