#include "Root/MeshManager/MeshManager.h"
#include "Root/LogManager/Log.h"

namespace ballistic
{
    bool MeshManager::Init() {
        LogDebug("Mesh manager initialized");
        return true;
    }

    void MeshManager::Shutdown() {

    }
    
} // namespace ballistic
