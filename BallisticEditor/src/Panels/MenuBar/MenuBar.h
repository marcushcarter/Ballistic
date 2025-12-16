#pragma once

#include <Ballistic.h>
#include "Panels/IPanel.h"

namespace Ballistic {

	class MenuBar : public IPanel {
	public:
        MenuBar(std::shared_ptr<ProjectManager> projectManager, std::shared_ptr<IWindow> window);
        
		void init() override;
		void OnImGuiRender() override;
		void onEvent(void* e) override;

    private:
        std::shared_ptr<ProjectManager> m_ProjectManager;
        std::shared_ptr<IWindow> m_Window;
	};
}