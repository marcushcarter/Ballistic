#pragma once

#include "bepch.h"
#include "Core/IWindow.h"

namespace Ballistic {

	class OglRenderer {
	public:
		OglRenderer() = default;
		explicit OglRenderer(IWindow* window) : m_Window(window) {}

		void Init();
		void Shutdown();
		void Render();

	private:

	    IWindow* m_Window = nullptr;

	};
}