#pragma once
#include "bepch.h"

namespace Ballistic {

	class IWindow;

	class OglRenderer {
	public:
		OglRenderer(std::shared_ptr<IWindow> window);

		void Init();
		void Shutdown();
		void Render();

		void requestResize(glm::vec2 dim);

		std::shared_ptr<gl::Texture2D> getTexture() const { return texture; }

	private:
	    std::shared_ptr<IWindow> m_Window;

		std::shared_ptr<gl::Shader> shader;
		std::shared_ptr<gl::Texture2D> texture;

		glm::vec2 m_ResizeSize;
		bool m_PendingResize;

	};
}