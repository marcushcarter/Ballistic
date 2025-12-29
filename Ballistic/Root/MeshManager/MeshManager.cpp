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

    GUID MeshManager::AddMesh(const std::string& name, const std::vector<Vertex>& verts, const std::vector<uint32_t>& inds) {
        MeshMetadata meta;
        meta.guid = GUID::Create();
        meta.name = name;
        meta.vertexOffset = m_vertices.size();
        meta.vertexCount = verts.size();
        meta.indexOffset = m_indices.size();
        meta.indexCount = inds.size();

        m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());
        m_indices.insert(m_indices.end(), inds.begin(), inds.end());
        m_metadata.push_back(meta);

        size_t idx = m_metadata.size() - 1;
        guidToIndex[meta.guid] = idx;
        m_metadataDirty.push_back(idx);

        LogInfo("Mesh '", name, "' Loaded succesfully");
        return meta.guid;
    }

    void MeshManager::Clear() {
        m_vertices.clear();
        m_indices.clear();
        m_metadata.clear();
        m_metadataDirty.clear();
        guidToIndex.clear();
    }

    void MeshManager::MarkDirty(GUID guid) {
        auto it = guidToIndex.find(guid);
        if (it != guidToIndex.end()) {
            size_t idx = it->second;
            m_metadataDirty.push_back(idx);
        }
    }

    const MeshMetadata* MeshManager::GetMeshMetadata(GUID guid) const {
        auto it = guidToIndex.find(guid);
        if (it != guidToIndex.end())
            return &m_metadata[it->second];
        return nullptr;
    }
    
} // namespace ballistic
