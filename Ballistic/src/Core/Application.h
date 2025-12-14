#pragma once

#include "bepch.h"
#include "Core/IWindow.h"
#include "Layers/LayerStack.h"
#include "Renderer/IRenderer.h"
#include "Renderer/RendererAPI.h"

namespace Ballistic {

	class RenderLayer;
	class EditorLayer;
	class RuntimeLayer;

	struct LayerContext {
	    LayerStack* layerStack;
	    IWindow* window;
	    IRenderer* renderer;
	};

	class Application {
	public:
		Application(WindowProps windowProps = WindowProps{}, WindowAPI windowAPI = WindowAPI::GLFW);
		virtual ~Application() = default;
		void run();

	protected:
		LayerStack m_LayerStack;

		std::shared_ptr<IWindow> m_Window;
		WindowAPI m_WindowAPI;

		std::weak_ptr<RenderLayer> m_RenderLayer;
		std::unique_ptr<IRenderer> m_Renderer;

		virtual void Shutdown();
	};

	Application* CreateApplication();
}