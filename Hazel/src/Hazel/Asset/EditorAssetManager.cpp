#include "hzpch.h"

#include "EditorAssetManager.h"
#include "AssetImporter.h"

namespace Hazel {


 
    bool EditorAssetManager::IsAssetHandleValid(AssetHandle handle) const
    {
        return handle != 0 && m_AssetRegistry.find(handle) != m_AssetRegistry.end();
    }


    bool EditorAssetManager::IsAssetLoaded(AssetHandle handle) const
    {
        return m_LoadedAssets.find(handle) != m_LoadedAssets.end();
    }

    const AssetMetadata& EditorAssetManager::GetMetaData(AssetHandle handle) const
    {
        static AssetMetadata s_NullMetadata;
        auto it = m_AssetRegistry.find(handle);
        if (it == m_AssetRegistry.end())
            return s_NullMetadata;

        return it->second;
    }

    Ref<Asset> EditorAssetManager::GetAsset(AssetHandle handle) const
    {
        if (!IsAssetHandleValid(handle))
            return nullptr;
        
        Ref<Asset> asset;
        if (IsAssetLoaded(handle))
        {
            Ref<Asset> asset = m_LoadedAssets.at(handle);
        }
        else
        {
            const AssetMetadata& metadata = GetMetaData(handle);
            Ref<Asset> asset = AssetImporter::ImportAsset(handle, metadata);
            if (!asset) 
            {
                // Import Failed
                HZ_CORE_ERROR("EditorAssetManager::GetAsset - asset import failed");
            }
        }
        return asset;
    }


}

