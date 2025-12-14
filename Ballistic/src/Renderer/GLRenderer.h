#pragma once

#include "bepch.h"
#include "IRenderer.h"

namespace Ballistic {

	class GLRenderer : public IRenderer {
	public:
		GLRenderer() = default;

		void Init() override;
		void Shutdown() override;

	private:
		// opengl context
	};
}