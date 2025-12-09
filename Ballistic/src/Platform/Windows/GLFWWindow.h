#pragma once

#include <GLFW/glfw3.h>
#include "Core/IWindow.h"

namespace Ballistic {

	class GLFWWindowIMPL : public IWindow {
	public:
		GLFWWindowIMPL(const WindowProps& windowProps);
		~GLFWWindowIMPL();

		void onUpdate();

		bool shouldClose() override;

	private:
		GLFWwindow* m_NativeWindow;
		
	};
}