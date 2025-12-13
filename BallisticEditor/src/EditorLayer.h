#pragma once

#include <Ballistic.h>

namespace Ballistic {

	class EditorLayer : public Layer {
	public:
		EditorLayer(const LayerContext& context, const std::string name = "EditorLayer")
			: Layer(name), m_LayerStack(context.layerStack) {}

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(void* e) override;

	private:
		LayerStack* m_LayerStack = nullptr;
	};
}