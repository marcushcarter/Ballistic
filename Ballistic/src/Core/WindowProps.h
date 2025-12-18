#pragma once
#include "bepch.h"

namespace Ballistic {

	struct WindowProps {
		std::string title;
		int width;
		int height;
		bool VSync;
		bool customTitleBar;

		WindowProps(const std::string& title = "BallisticEngine", int width = 1280, int height = 720, bool customTitleBar = false, bool VSync = false)
			: title(title), width(width), height(height), VSync(VSync), customTitleBar(customTitleBar) {}
	};
}