#pragma once
#include "bepch.h"

namespace Ballistic {

	struct WindowProps {
		std::string title;
		int width;
		int height;
		bool vsync;

		WindowProps(const std::string& title = "BallisticEngine", int width = 1280, int height = 720, bool vsync = false)
			: title(title), width(width), height(height), vsync(vsync) {}
	};
}