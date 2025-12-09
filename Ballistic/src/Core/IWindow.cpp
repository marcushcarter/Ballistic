#include "Core/IWindow.h"
#include "Platform/Windows/GLFWWindow.h"

namespace Ballistic {

	std::shared_ptr<IWindow> IWindow::createWindow(const WindowProps windowProps) {
		return std::make_shared<GLFWWindowIMPL>(windowProps);
	}
}