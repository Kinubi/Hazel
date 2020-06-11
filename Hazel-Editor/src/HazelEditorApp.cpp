#include <Hazel.h>
#include <Hazel/Core/Entrypoint.h>

#include "EditorLayer.h"


namespace Hazel {

	class HazelEditor : public Application
	{
	public:
		HazelEditor()
			: Application("Hazel Editor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~HazelEditor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	}
}