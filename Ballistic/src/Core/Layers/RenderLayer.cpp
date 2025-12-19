#include "RenderLayer.h"
#include "Event.h"
#include "LayerStack.h"
#include "Core/Application.h"
#include "Renderer/IRenderer.h"

namespace Ballistic {

	RenderLayer::RenderLayer(const LayerContext& context, const std::string name) : Layer(name) {
		m_layerStack = context.layerStack;
		m_renderer = context.renderer;
	}

	void RenderLayer::OnAttach() {
	}

	void RenderLayer::OnDetach() {
	}

	void RenderLayer::OnUpdate() {
		m_renderer->Render();
		
		// Event e(EventType::TestEvent, nullptr);
		// m_LayerStack->dispatchEvent(&e);
	}

	void RenderLayer::OnEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}