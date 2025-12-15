#pragma once

#include "bepch.h"
#include "Core/IWindow.h"
#include "Layers/LayerStack.h"
#include "Renderer/OglRenderer.h"

namespace Ballistic {

	class RenderLayer;
	class EditorLayer;
	class RuntimeLayer;

	struct LayerContext {
	    LayerStack* layerStack;
	    IWindow* window;
	    OglRenderer* renderer;
	};

	class Application {
	public:
		Application(WindowProps windowProps = WindowProps{});
		virtual ~Application() = default;
		void run();

	protected:
		LayerStack m_LayerStack;

		std::shared_ptr<IWindow> m_Window;

		std::weak_ptr<RenderLayer> m_RenderLayer;
		std::unique_ptr<OglRenderer> m_OglRenderer;

		virtual void Shutdown();
	};

	Application* CreateApplication();
}