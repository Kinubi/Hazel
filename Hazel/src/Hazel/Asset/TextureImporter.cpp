#include "hzpch.h"
#include "TextureImporter.h"

#include <stb_image.h>

namespace Hazel {



	Ref<Asset> TextureImporter::ImportTexture2D(AssetHandle handle, const AssetMetadata& metadata)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		Buffer data;
		{
			HZ_PROFILE_SCOPE("stbi_load - TextureImporter::ImportTexture2D");
			std::string pathStr = metadata.FilePath.string();
			data.Data = stbi_load(pathStr.c_str(), &width, &height, &channels, 0);
		}

		if (data.Data == nullptr)
		{
			HZ_CORE_ERROR("Could not load Texture from filepath: {}", metadata.FilePath.string());
			return nullptr;
		}

		// TODO: Let Cherno think about this
		data.Size = width * height * channels;

		TextureSpecification spec;
		spec.Width = width;
		spec.Height = height;
		switch (channels)
		{
		case 3:
			spec.Format = ImageFormat::RGB8;
			break;
		case 4:
			spec.Format = ImageFormat::RGBA8;
			break;
		}

		Ref<Texture2D> texture = Texture2D::Create(spec, data);
		data.Release();

		return texture;
	}

}