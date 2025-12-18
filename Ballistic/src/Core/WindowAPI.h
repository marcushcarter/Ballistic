#pragma once
#include "bepch.h"

namespace Ballistic {

	class WindowAPI {
	public:
		enum class API {
			None = 0,
			GLFW = 1,
		};

		static API GetAPI() { return s_API; }
		static void SetAPI(API api) { s_API = api; }

	private:
		static API s_API;
	};

}