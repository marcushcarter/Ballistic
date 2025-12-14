#pragma once

#include <Ballistic.h>
#include "Panels/IPanel.h"

namespace Ballistic {

	class DemoPanel : public IPanel {
	public:
		void init() override;
		void OnImGuiRender() override;
		void onEvent(void* e) override;

	};
}