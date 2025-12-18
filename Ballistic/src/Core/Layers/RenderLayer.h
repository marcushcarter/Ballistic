#pragma once
#include "bepch.h"
#include "Layer.h"

namespace Ballistic {

	struct LayerContext;
	class Layer;
	class LayerStack;
	class OglRenderer;

	class RenderLayer : public Layer {
	public:
		RenderLayer(const LayerContext& context, const std::string name = "RenderLayer");

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(void* e) override;

	private:
		std::shared_ptr<LayerStack> m_LayerStack;
        std::shared_ptr<OglRenderer> m_OglRenderer;
	};
}