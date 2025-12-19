#pragma once
#include "bepch.h"

namespace Ballistic {

	class WindowAPI {
	public:
		enum class API {
			None = 0,
			GLFW = 1,
		};

		static API GetAPI() { return s_api; }
		static void SetAPI(API api) { s_api = api; }

	private:
		static API s_api;
	};

}