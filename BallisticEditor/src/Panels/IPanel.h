#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "IconsFontAwesome5.h"

namespace Ballistic {

	class IPanel {
	public:
		virtual ~IPanel() = default;
		
		virtual void Init() = 0;
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(void* ePtr) = 0;
	};
}