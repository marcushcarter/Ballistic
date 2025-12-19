#pragma once
#include "bepch.h"

namespace Ballistic {

	struct WindowProps;
	class WindowAPI;
	
	class IWindow {
	public:
		virtual ~IWindow() = default;

		virtual void OnUpdate() = 0;
		virtual bool ShouldClose() const = 0;

		virtual void ToggleFullscreen(bool fullscreen) = 0;
		virtual bool IsFullscreen() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual WindowProps GetWindowProps() const = 0;
	};

}