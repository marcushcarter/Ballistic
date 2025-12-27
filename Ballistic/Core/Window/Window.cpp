#include "Core/Window/Window.h"
#include "Core/Window/WindowInfo.h"

namespace ballistic
{
    bool Window::Init(const WindowSettings& windowSettings)
    {
        m_settings = windowSettings;

        if (!glfwInit())
            return false;
        
        m_nativeWindow = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.title.c_str(), nullptr, nullptr);

        return true;
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_nativeWindow);
    }

    void Window::Update() {
        glfwPollEvents();
        glfwSwapBuffers(m_nativeWindow);
    }

    void Window::Shutdown() {
        
    }

} // namespace ballistic
