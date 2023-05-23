#pragma once

#include "Asset.h"

#include <filesystem>

namespace Hazel {

	struct AssetMetadata
	{
		AssetType Type;
		std::filesystem::path FilePath;

		operator bool() const { return Type != AssetType::None; }
	};

}