#pragma once

#include "AssetMetadata.h"
#include "AssetManagerBase.h"

namespace Hazel {

	using AssetRegistry = std::map<AssetHandle, AssetMetadata>;

	class EditorAssetManager : public AssetManagerBase
	{
	public:
		virtual bool IsAssetLoaded(AssetHandle handle) const override;
		virtual bool IsAssetHandleValid(AssetHandle handle) const override;
		virtual Ref<Asset> GetAsset(AssetHandle handle) const override;

		const AssetMetadata& GetMetaData(AssetHandle handle) const;
	private:
		AssetRegistry m_AssetRegistry;
		AssetMap m_LoadedAssets;

		// TODO: Memory only assets
	};

}

