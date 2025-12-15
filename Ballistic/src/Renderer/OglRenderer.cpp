#include "OglRenderer.h"

namespace Ballistic {

	OglRenderer::OglRenderer(std::shared_ptr<IWindow> window) {
		m_Window = window;
	}
	
	void OglRenderer::Init() {
		std::cout << "OpenGL Renderer Initialized" << std::endl;
	}
	
	void OglRenderer::Shutdown() {
	}

	void OglRenderer::Render() {
	}
}