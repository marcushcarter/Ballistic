#pragma once
#include "bepch.h"

namespace Ballistic {

    class Scene;

    class SceneManager {
    public:
        SceneManager() = default;

        std::shared_ptr<Scene> createScene(const std::string& name);
        void destroyScene(const std::string& name);

        void setActiveScene(const std::string& name);
        std::shared_ptr<Scene> getActiveScene() const;
        
        std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
        std::shared_ptr<Scene> m_activeScene = nullptr;

    private:
    };
    
}