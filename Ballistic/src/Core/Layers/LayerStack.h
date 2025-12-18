#pragma once
#include "bepch.h"

namespace Ballistic {

	class Layer;

	class LayerStack {
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void pushLayer(std::shared_ptr<Layer> layer);
		void popLayer(std::shared_ptr<Layer> layer);

		void onUpdate();
		void onDetach();
		void dispatchEvent(void* e);

	public:
		std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}