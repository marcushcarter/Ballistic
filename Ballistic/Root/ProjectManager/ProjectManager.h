#pragma once
#include "bepch.h"

namespace ballistic
{
    class ProjectManager
    {
    public:
        ProjectManager() = default;
        ~ProjectManager() { Shutdown(); }

        bool Init();
        void Shutdown();

        bool CreateNewProject(const std::filesystem::path& parentPath, const std::string& name = "New Project");
        bool OpenProject(const std::filesystem::path& configPath);

        const std::string& GetName() const { return m_projectName; }
        const std::filesystem::path& GetProjectRoot() const { return m_projectRoot; }

    private:
        std::string m_projectName;
        std::filesystem::path m_projectRoot;
    };

} // namespace ballistic