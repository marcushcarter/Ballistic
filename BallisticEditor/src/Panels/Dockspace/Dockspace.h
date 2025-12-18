#pragma once
#include <Ballistic.h>
#include "Panels/IPanel.h"

namespace Ballistic {

	class Dockspace : public IPanel {
	public:        
		void init() override;
		void OnImGuiRender() override;
		void onEvent(void* e) override;
	};
}