#include "RenderLayer.h"
#include "Event.h"
#include "LayerStack.h"
#include "Core/Application.h"
#include "Renderer/OglRenderer.h"

namespace Ballistic {

	RenderLayer::RenderLayer(const LayerContext& context, const std::string name) : Layer(name) {
		m_LayerStack = context.layerStack;
		m_OglRenderer = context.renderer;
	}

	void RenderLayer::onAttach() {
	}

	void RenderLayer::onDetach() {
	}

	void RenderLayer::onUpdate() {
		m_OglRenderer->Render();
		
		// Event e(EventType::TestEvent, nullptr);
		// m_LayerStack->dispatchEvent(&e);
	}

	void RenderLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}