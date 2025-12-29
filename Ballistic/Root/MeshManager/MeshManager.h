#pragma once
#include "bepch.h"
#include "Root/MeshManager/Vertex.h"
#include "Root/MeshManager/MeshMetaData.h"

namespace ballistic
{
    class MeshManager
    {
    public:
        MeshManager() = default;
        ~MeshManager() { Shutdown(); }

        bool Init();
        void Shutdown();

        // GUID AddMesh(const std::string& name, const std::vector<Vertex>& verts, const std::vector<uint32_t>& inds);

        // void Clear();
        // void ClearDirty();

        const std::vector<Vertex>& GetVertexBuffer() const;
        const std::vector<uint32_t>& GetIndexBuffer() const;
        const std::vector<MeshMetadata>& GetAllMetadata() const;
        const std::vector<size_t>& GetDirtyMetadata() const;

        const MeshMetadata* GetMeshMetadata(GUID guid) const;

    private:
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;

        std::vector<MeshMetadata> m_metadata;
        std::vector<size_t> m_metadataDirty;

        std::unordered_map<GUID, size_t> guidToIndex;
    };
    
} // namespace ballistic
