#pragma once

#include <Ballistic.h>

namespace Ballistic {

	class RuntimeLayer : public Layer {
	public:
		RuntimeLayer(const LayerContext& context, const std::string name = "RuntimeLayer");

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(void* e) override;

	private:
		std::shared_ptr<LayerStack> m_LayerStack;
		
        std::shared_ptr<IWindow> m_Window;
        std::shared_ptr<OglRenderer> m_OglRenderer;
	};
}