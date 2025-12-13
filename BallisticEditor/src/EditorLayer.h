#pragma once

#include <Ballistic.h>

namespace Ballistic {

	class EditorLayer : public Layer {
	public:
		EditorLayer(const LayerContext& context, const std::string name = "EditorLayer")
			: Layer(name), m_LayerStack(context.layerStack), m_Window(context.window), m_Renderer(context.renderer) {}

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(void* e) override;

	private:
		LayerStack* m_LayerStack = nullptr;

        IWindow* m_Window = nullptr;
        IRenderer* m_Renderer = nullptr;
	};
}