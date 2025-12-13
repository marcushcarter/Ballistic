#pragma once

#include "bepch.h"
#include "Core/IWindow.h"

namespace Ballistic {
	
	class GLFWWindow : public IWindow {
	public:
		GLFWWindow(RendererAPI api, const WindowProps& windowProps);
		~GLFWWindow();

		void onUpdate() override;
		bool shouldClose() const override;

		void* get() const override { return m_NativeWindow; }
		WindowProps getProps() const override { return m_Props; }
		WindowAPI getAPI() const override { return WindowAPI::GLFW; }

		static std::shared_ptr<IWindow> Create(RendererAPI rendererAPI, const WindowProps& windowProps = {});

	private:
		GLFWwindow* m_NativeWindow;
		WindowProps m_Props;
	};

}