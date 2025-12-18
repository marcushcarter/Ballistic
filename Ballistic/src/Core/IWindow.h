#pragma once
#include "bepch.h"

namespace Ballistic {

	struct WindowProps;
	class WindowAPI;
	
	class IWindow {
	public:
		virtual ~IWindow() = default;

		virtual void onUpdate() = 0;
		virtual bool shouldClose() const = 0;

		virtual void toggleFullscreen(bool fullscreen) = 0;
		virtual bool isFullscreen() const = 0;

		virtual void* get() const = 0;
		virtual WindowProps getProps() const = 0;
	};

}