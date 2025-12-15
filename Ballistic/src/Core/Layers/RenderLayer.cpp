#include "RenderLayer.h"
#include "Event.h"

namespace Ballistic {

	void RenderLayer::onAttach() {
	}

	void RenderLayer::onDetach() {
	}

	void RenderLayer::onUpdate() {
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
	}
}