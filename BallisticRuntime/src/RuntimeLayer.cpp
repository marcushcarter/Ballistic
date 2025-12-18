#include "RuntimeLayer.h"

namespace Ballistic {

	RuntimeLayer::RuntimeLayer(const LayerContext& context, const std::string name) : Layer(name) {
		m_LayerStack = context.layerStack;
		m_Window = context.window;
		m_OglRenderer = context.renderer;
	}

	void RuntimeLayer::onAttach() {
		
		const char* vertexShaderSrc = R"(
		#version 460 core
		out vec2 TexCoords;
		void main() {
			const vec2 verts[3] = vec2[3](
				vec2(-1.0, -1.0),
				vec2( 3.0, -1.0),
				vec2(-1.0,  3.0)
			);
			gl_Position = vec4(verts[gl_VertexID], 0.0, 1.0);
			TexCoords = (gl_Position.xy + 1.0) * 0.5;
		}
		)";
		
		const char* fragmentShaderSrc = R"(
		#version 460 core
		in vec2 TexCoords;
		out vec4 FragColor;
		uniform sampler2D screenTexture;
		void main() {
			FragColor = vec4(1.0, 1.0, 1.0, 1.0);
			FragColor = texture(screenTexture, TexCoords);
		}
		)";
		
		blitShader = std::make_shared<gl::Shader>();
		blitShader->create();
		blitShader->attachShader(GL_VERTEX_SHADER, vertexShaderSrc);
		blitShader->attachShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
		blitShader->link();

		vao = std::make_shared<gl::VertexArray>();
		vao->create();
	}

	void RuntimeLayer::onDetach() {
	}

	void RuntimeLayer::onUpdate() {
		auto windowProps = m_Window->getProps();
		m_OglRenderer->requestResize(glm::vec2(windowProps.width, windowProps.height));
		// resize camera

		auto texture = m_OglRenderer->getTexture();

		gl::State::bindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		gl::Viewport(0, 0, texture->width(), texture->height());

		blitShader->use();
		texture->bind(0);
		blitShader->setUniform<int>("screenTexture", 0);

		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		vao->unbind();
	}

	void RuntimeLayer::onEvent(void* ePtr) {
		Event* e = static_cast<Event*>(ePtr);
		// if (e->getType() == EventType::TestEvent) {
		// 	std::cout << "Event passed from Render Layer to Runtime Layer" << std::endl;
	    // }
	}
}