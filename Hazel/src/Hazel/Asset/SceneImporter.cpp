#include "hzpch.h"
#include "AssetImporter.h"

#include "Hazel/Scene/SceneSerializer.h"
#include "Hazel/Project/Project.h"

#include <map>
#include "SceneImporter.h"

namespace Hazel {



	Ref<Scene> SceneImporter::ImportScene(AssetHandle handle, const AssetMetadata& metadata)
	{
		HZ_PROFILE_FUNCTION();
		return LoadScene(Project::GetAssetDirectory() / metadata.FilePath);
	}

	Ref<Scene> SceneImporter::LoadScene(const std::filesystem::path& path)
	{
		HZ_PROFILE_FUNCTION();
		Ref<Scene>  scene = CreateRef<Scene>();
		SceneSerializer serializer(scene);
		serializer.Deserialize(path);

		return scene;
	}

	void SceneImporter::SaveScene(Ref<Scene> scene, const std::filesystem::path& path)
	{
		HZ_PROFILE_FUNCTION();
		SceneSerializer serializer(scene);
		serializer.Serialize(Project::GetAssetDirectory() / path);
	}

}