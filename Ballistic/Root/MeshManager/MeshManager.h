#pragma once
#include "bepch.h"

namespace ballistic
{
    class MeshManager
    {
    public:
        MeshManager() = default;
        ~MeshManager() { Shutdown(); }

        bool Init();
        void Shutdown();

    private:
    };
    
} // namespace ballistic
