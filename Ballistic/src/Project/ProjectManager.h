#pragma once

#include "lrpch.h"
#include "Assets/AssetPool.h"
// #include "Scene/SceneManager.h"

namespace Ballistic {

	class ProjectManager {
	public:
		ProjectManager() {
			// m_SceneManager = std::make_shared<SceneManager>();
			m_AssetPool = std::make_shared<AssetPool>();
		}

		~ProjectManager() = default;

		// std::shared_ptr<SceneManager> GetAssetPool() const { return m_SceneManager; }
		std::shared_ptr<AssetPool> GetAssetPool() const { return m_AssetPool; }

	private:
		// std::shared_ptr<SceneManager> m_SceneManager;
		std::shared_ptr<AssetPool> m_AssetPool;
	};

};	