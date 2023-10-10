#include "hzpch.h"

#include "EditorAssetManager.h"
#include "AssetImporter.h"
#include "Hazel/Project/Project.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Hazel {

    static std::map<std::filesystem::path, AssetType> s_AssetExtensionMap = {
        { ".hazel", AssetType::Scene },
        { ".png", AssetType::Texture2D },
        { ".jpg", AssetType::Texture2D },
        { ".jpeg", AssetType::Texture2D }
    };

    static AssetType GetAssetTypeFromExtension(const std::filesystem::path& extension)
    {
        if (s_AssetExtensionMap.find(extension) == s_AssetExtensionMap.end())
        {
            HZ_CORE_WARN("Could not find AssetType for {}", extension);
            return AssetType::None;
        }

        return s_AssetExtensionMap.at(extension);
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const std::string_view& v)
    {
        out << std::string(v.data(), v.size());
        return out;
    }
 
    bool EditorAssetManager::IsAssetHandleValid(AssetHandle handle) const
    {
        return handle != 0 && m_AssetRegistry.find(handle) != m_AssetRegistry.end();
    }

    AssetType EditorAssetManager::GetAssetType(AssetHandle handle) const
    {
        if (!IsAssetHandleValid(handle))
            return AssetType::None;

        return m_AssetRegistry.at(handle).Type;
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



    Ref<Asset> EditorAssetManager::GetAsset(AssetHandle handle)
    {
        if (!IsAssetHandleValid(handle))
            return nullptr;
        
        Ref<Asset> asset;
        if (IsAssetLoaded(handle))
        {
            asset = m_LoadedAssets.at(handle);
        }
        else
        {
            const AssetMetadata& metadata = GetMetaData(handle);
            asset = AssetImporter::ImportAsset(handle, metadata);
            if (!asset) 
            {
                // Import Failed
                HZ_CORE_ERROR("EditorAssetManager::GetAsset - asset import failed");
            }
            m_LoadedAssets[handle] = asset;
        }
        return asset;
    }

    void EditorAssetManager::ImportAsset(const std::filesystem::path filepath)
    {
        AssetHandle handle;
        AssetMetadata metadata;
        metadata.FilePath = filepath;
        metadata.Type = GetAssetTypeFromExtension(filepath.extension());
        Ref<Asset> asset = AssetImporter::ImportAsset(handle, metadata);
        if (asset)
        {
            asset->Handle = handle; 
            m_LoadedAssets[handle] = asset;
            m_AssetRegistry[handle] = metadata;
            SerializeAssetRegistry();
        }
    }

    void EditorAssetManager::SerializeAssetRegistry()
    {
        auto path = Project::GetActiveAssetRegistryPath();


        YAML::Emitter out;
        {
            out << YAML::BeginMap; // Root
            out << YAML::Key << "AssetRegistry" << YAML::Value;

            out << YAML::BeginSeq;
            for (const auto&[handle, metadata] : m_AssetRegistry)
            {
                out << YAML::BeginMap;// Asset
                out << YAML::Key << "Handle" << YAML::Value << handle;
                std::string filepathStr = metadata.FilePath.generic_string();
                out << YAML::Key << "FilePath" << YAML::Value << filepathStr;
                out << YAML::Key << "Type" << YAML::Value << AssetTypeToString(metadata.Type);

                out << YAML::EndMap; // Asset
            }
            out << YAML::EndSeq;
            out << YAML::EndMap; // Root
        }

        std::ofstream fout(path);
        fout << out.c_str();
    }

    bool EditorAssetManager::DeserializeAssetRegistry()
    {
        auto path = Project::GetActiveAssetRegistryPath();
        YAML::Node data;

        try
        {
            data = YAML::LoadFile(path.string());
        }
        catch (YAML::ParserException e)
        {
            HZ_CORE_ERROR("Failed to load project file '{0}'\n      {1}", path, e.what());
            return false;
        }

        auto rootNode = data["AssetRegistry"];
        if (!rootNode)
            return false;

        for (const auto& node : rootNode)
        {
            AssetHandle handle = node["Handle"].as<uint64_t>();
            auto& metadata = m_AssetRegistry[handle];

            metadata.FilePath = node["FilePath"].as<std::string>();
            metadata.Type = AssetTypeFromString(node["Type"].as<std::string>());
        }

        return true;

    }


}

