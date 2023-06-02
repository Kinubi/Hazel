#pragma once

#include "Asset.h"
#include "AssetMetadata.h"

#include "Hazel/Renderer/Texture.h"

namespace Hazel {

	class TextureImporter
	{
	public:
		static Ref<Asset> ImportTexture2D(AssetHandle handle, const AssetMetadata& metadata);


	};


}

