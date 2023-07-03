#pragma once

#include "AssetMetadata.h"
#include "AssetManagerBase.h"

namespace Hazel {

	using AssetRegistry = std::map<AssetHandle, AssetMetadata>;

	class EditorAssetManager : public AssetManagerBase
	{
	public:
		virtual Ref<Asset> GetAsset(AssetHandle handle) override;

		virtual bool IsAssetLoaded(AssetHandle handle) const override;
		virtual bool IsAssetHandleValid(AssetHandle handle) const override;

		virtual AssetType GetAssetType(AssetHandle handle) const override;

		void ImportAsset(const std::filesystem::path filepath);

		const AssetMetadata& GetMetaData(AssetHandle handle) const;

		const AssetRegistry& GetAssetRegistry() { return m_AssetRegistry; };

		void SerializeAssetRegistry();
		bool DeserializeAssetRegistry();
	private:
		AssetRegistry m_AssetRegistry;
		AssetMap m_LoadedAssets;

		// TODO: Memory only assets
	};

}

