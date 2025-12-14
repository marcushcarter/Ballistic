#pragma once

#include <Ballistic.h>
#include <imgui.h>
#include "Panels/IPanel.h"

namespace Ballistic {

	class DemoPanel : public IPanel {
	public:
		void Init() override {
		}
		void OnImGuiRender() override {
			
			ImGui::Begin("Demo Panel");

	        ImGui::Text("Hello from DemoPanel!");
	        if (ImGui::Button("Click Me")) {
	            // m_ClickCount++;
	            // std::cout << "Button clicked " << m_ClickCount << " times\n";
	        }

	        // ImGui::Text("Click count: %d", m_ClickCount);

	        ImGui::End();
		}
		void onEvent(void* e) override {}

	};
}