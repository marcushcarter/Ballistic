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
    
    const std::vector<Vertex>& MeshManager::GetVertexBuffer() const { return m_vertices; }
    const std::vector<uint32_t>& MeshManager::GetIndexBuffer() const { return m_indices; }
    const std::vector<MeshMetadata>& MeshManager::GetAllMetadata() const { return m_metadata; }
    const std::vector<size_t>& MeshManager::GetDirtyMetadata() const { return m_metadataDirty; }

    const MeshMetadata* MeshManager::GetMeshMetadata(GUID guid) const {
        auto it = guidToIndex.find(guid);
        if (it != guidToIndex.end())
            return &m_metadata[it->second];
        return nullptr;
    }
    
} // namespace ballistic
