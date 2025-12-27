#pragma once
#include "bepch.h"

namespace ballistic
{

    class IApplication
    {
    public:
        IApplication() = default;
        virtual ~IApplication() = default;

        virtual bool Init() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Shutdown() = 0;

        void SetExeDirectory(const std::filesystem::path& path) { m_exeDir = path; }
        const std::filesystem::path& GetExeDirectory() const { return m_exeDir; }

    private:
        std::filesystem::path m_exeDir;
    };
    
} // namespace ballistic

