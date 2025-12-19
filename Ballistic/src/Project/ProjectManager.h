#pragma once
#include "bepch.h"

namespace Ballistic {

    class SceneManager;
    class AssetManager;

    class ProjectManager {
    public:
        ProjectManager();

        std::string projectName;

        std::filesystem::path m_ProjectRoot;
        bool m_ProjectOpen = false;

        bool NewProject(const std::filesystem::path& folderpath);
        bool OpenProject(const std::filesystem::path& projectFilePath);
        bool SaveProject();
        bool CloseProject();

        std::shared_ptr<SceneManager> GetSceneManager() { return m_SceneManager; }
        std::shared_ptr<AssetManager> GetAssetManager() { return m_AssetManager; }

    private:
        std::shared_ptr<SceneManager> m_SceneManager;
        std::shared_ptr<AssetManager> m_AssetManager;
    };
    
}