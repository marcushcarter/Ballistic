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
		gl::ClearColor(1.0, 0.0, 1.0, 1.0);
		gl::Clear();

	}

	void RuntimeLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
		// if (e->getType() == EventType::TestEvent) {
		// 	std::cout << "Event passed from Render Layer to Runtime Layer" << std::endl;
	    // }
	}
}