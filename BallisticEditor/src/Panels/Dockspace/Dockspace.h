#pragma once
#include <Ballistic.h>
#include "Panels/IPanel.h"

namespace Ballistic {

	class Dockspace : public IPanel {
	public:        
		void Init() override;
		void OnImGuiRender() override;
		void OnEvent(void* ePtr) override;
	};
}