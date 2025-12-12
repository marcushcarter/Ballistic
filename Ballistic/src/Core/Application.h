#pragma once

#include "bepch.h"
#include "Platform/GLFW/GLFWWindow.h"
#include "Layers/LayerStack.h"
#include "Renderer/Renderer.h"

namespace Ballistic {

	class RenderLayer;
	class EditorLayer;
	class RuntimeLayer;

	struct LayerContext {
	    LayerStack* layerStack;
	    GLFWWindow* window;
	    Renderer* renderer;
	};

	class Application {
	public:
		Application(WindowProps windowProps = WindowProps{});
		virtual ~Application() = default;
		void run();

	protected:
		std::shared_ptr<GLFWWindow> m_Window;

		LayerStack m_LayerStack;
		std::weak_ptr<RenderLayer> m_RenderLayer;

		std::unique_ptr<Renderer> m_Renderer;

		virtual void Shutdown();
	};

	Application* CreateApplication();
}