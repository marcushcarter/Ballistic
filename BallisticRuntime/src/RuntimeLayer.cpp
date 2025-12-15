#include "RuntimeLayer.h"

namespace Ballistic {

	RuntimeLayer::RuntimeLayer(const LayerContext& context, const std::string name) : Layer(name) {
		m_LayerStack = context.layerStack;
		m_Window = context.window;
		m_OglRenderer = context.renderer;
	}

	void RuntimeLayer::onAttach() {
	}

	void RuntimeLayer::onDetach() {
	}

	void RuntimeLayer::onUpdate() {
	}

	void RuntimeLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}