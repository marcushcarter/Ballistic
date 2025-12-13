#pragma once

#include "bepch.h"
#include "IRenderer.h"

namespace Ballistic {

	class GLRenderer : public IRenderer {
	public:
		GLRenderer() = default;

		void Init() override;
		void Shutdown() override;

		RendererAPI getAPI() const override { return RendererAPI::OpenGL; }

	private:
		// opengl context
	};
}