#pragma once

#include "bepch.h"
#include "IRenderer.h"

namespace Ballistic {

	class VkRenderer : public IRenderer {
	public:
		VkRenderer() = default;

		void Init() override;
		void Shutdown() override;

		RendererAPI getAPI() const override { return RendererAPI::Vulkan; }

	private:
		// opengl context
	};
}