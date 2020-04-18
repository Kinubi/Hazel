#include "Hazel.h"

#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>



Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("assets/textures/2000px-Checkerboard_pattern.svg.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	Hazel::Renderer2D::ResetStats();

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Hazel::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, 45.0f, m_SquareColor);
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, m_Texture, 5.0f);
	Hazel::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 5.0f, 5.0f }, 45.0f, m_Texture, 5.0f);
	Hazel::Renderer2D::EndScene();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.1f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.1f)
		{
			glm::vec4 color = { ((x + 5.0f) / 10.0f), 0.3f, ((y + 5.0f) / 10.0f), 1.0f };
			Hazel::Renderer2D::DrawQuad({ x, y }, { 0.09f, 0.09f }, color);
		}
	}

	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Hazel::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indecis: %d", stats.GetTotalIndexCount());
	ImGui::Text("Frame time: %d");


	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
