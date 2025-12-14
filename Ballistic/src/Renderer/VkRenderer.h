#pragma once

#include "bepch.h"
#include "IRenderer.h"

namespace Ballistic {

	class VkRenderer : public IRenderer {
	public:
		VkRenderer() = default;

		void Init() override;
		void Shutdown() override;

	private:
		// opengl context
	};
}