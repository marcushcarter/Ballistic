#pragma once

#include "bepch.h"

namespace Ballistic {

	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
		};

		static API GetAPI() { return s_API; }
		static void SetAPI(API api) { s_API = api; }

	private:
		static API s_API;
	};
}