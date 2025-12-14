#pragma once

namespace Ballistic {

	class IPanel {
	public:
		virtual ~IPanel() = default;
		
		virtual void init() = 0;
		virtual void OnImGuiRender() = 0;
		virtual void onEvent(void* e) = 0;
	};
}