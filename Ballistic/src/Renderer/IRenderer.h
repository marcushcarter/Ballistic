#pragma once

#include "bepch.h"
#include "Core/PlatformAPI.h"

namespace Ballistic {

	class IRenderer {
	public:
		virtual ~IRenderer() {}

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual RendererAPI getAPI() const = 0;

	protected:

	};
}