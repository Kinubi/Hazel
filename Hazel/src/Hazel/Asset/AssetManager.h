#pragma once

#include "AssetManagerBase.h"

#include "Hazel/Project/Project.h"

namespace Hazel {
	class AssetManager
	{
	public:
		template<typename T>
		static Ref<T> GetAsset(AssetHandle handle)
		{
			return std::static_pointer_cast<T>(Project::GetActive()->GetAssetManager()->GetAsset(handle));
		}
	};
};

