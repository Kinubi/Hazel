#pragma once

#include <string>
#include <filesystem>

#include "Hazel/Core/Base.h"

#include "Hazel/Asset/RuntimeAssetManager.h"
#include "Hazel/Asset/EditorAssetManager.h"

namespace Hazel {

	struct ProjectConfig
	{
		std::string Name = "Untitled";

		AssetHandle StartScene;

		std::filesystem::path AssetDirectory;
		std::filesystem::path AssetRegistryPath;
		std::filesystem::path ScriptModulePath;
	};

	class Project
	{
	public:
		const std::filesystem::path& GetProjectDirectory() { return m_ProjectDirectory; }

		std::filesystem::path GetAssetDirectory() { return GetProjectDirectory() / m_Config.AssetDirectory; }
		
		std::filesystem::path GetAssetRegistryPath() { return GetAssetDirectory() / m_Config.AssetRegistryPath; }

		// TODO(Yan): move to asset manager when we have one
		std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& path) { return GetAssetDirectory() / path; }
		
		std::filesystem::path GetAssetAbsolutePath(const std::filesystem::path& path) { return GetAssetDirectory() / path; }

		static const std::filesystem::path& GetActiveProjectDirectory()
		{
			HZ_CORE_ASSERT(s_ActiveProject);
			return s_ActiveProject->m_ProjectDirectory;
		}

		static std::filesystem::path GetActiveAssetDirectory()
		{
			HZ_CORE_ASSERT(s_ActiveProject);
			return s_ActiveProject->GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
		}		
		
		static std::filesystem::path GetActiveAssetRegistryPath()
		{
			HZ_CORE_ASSERT(s_ActiveProject);
			return s_ActiveProject->GetAssetDirectory() / s_ActiveProject->m_Config.AssetRegistryPath;
		}

		// TODO(Yan): move to asset manager when we have one
		static std::filesystem::path GetActiveAssetFileSystemPath(const std::filesystem::path& path)
		{
			HZ_CORE_ASSERT(s_ActiveProject);
			return s_ActiveProject->GetAssetDirectory() / path;
		}


		ProjectConfig& GetConfig() { return m_Config; }

		static Ref<Project> GetActive() { return s_ActiveProject; }
		std::shared_ptr<AssetManagerBase> GetAssetManager() { return m_AssetManager; }
		std::shared_ptr<RuntimeAssetManager> GetRuntimeAssetManager() { return std::static_pointer_cast<RuntimeAssetManager>(m_AssetManager); }
		std::shared_ptr<EditorAssetManager> GetEditorAssetManager() { return std::static_pointer_cast<EditorAssetManager>(m_AssetManager); }

		static Ref<Project> New();
		static Ref<Project> Load(const std::filesystem::path& path);
		static bool SaveActive(const std::filesystem::path& path);
	private:
		ProjectConfig m_Config;
		std::filesystem::path m_ProjectDirectory;
		std::shared_ptr<AssetManagerBase> m_AssetManager;

		inline static Ref<Project> s_ActiveProject;
	};

}