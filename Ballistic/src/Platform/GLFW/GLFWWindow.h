#pragma once
#include "bepch.h"
#include "Core/IWindow.h"
#include "Core/WindowProps.h"
#include "Core/WindowAPI.h"

namespace Ballistic {
	
	class GLFWWindow : public IWindow {
	public:
		GLFWWindow(const WindowProps& windowProps);
		~GLFWWindow();

		void OnUpdate() override;
		bool ShouldClose() const override;

		void ToggleFullscreen(bool fullscreen) override;
		bool IsFullscreen() const override;

		void* GetNativeWindow() const override { return m_nativeWindow; }
		WindowProps GetWindowProps() const override { return m_windowProps; }

		static std::shared_ptr<IWindow> Create(const WindowProps& windowProps = {});

	private:
		GLFWwindow* m_nativeWindow;
		WindowProps m_windowProps;

		int m_WindowedX = 0, m_WindowedY = 0, m_WindowedW = 1280, m_WindowedH = 720;
	};

}