#include "Sandbox2D.h"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach() {
	
	m_CheckerTex = Maple::Texture2D::Create("assets/textures/checker.png");

}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Maple::Timestep ts) {
	// Update camera
	m_CameraController.OnUpdate(ts);

	// Render
	Maple::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Maple::RenderCommand::Clear();

	Maple::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Maple::Renderer2D::DrawQuad(m_SquarePosition, m_SquareRotation, m_SquareSize, m_SquareColor);
		Maple::Renderer2D::DrawQuad({ -0.25f, 0.25f }, 45.0f, { 0.75f, 0.5f }, { 0.2f, 0.7f, 0.3f, 1.0f });
		Maple::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, 0.0f, { 10.0f, 10.0f }, m_CheckerTex);
	}
	Maple::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Material Settings");
	ImGui::ColorEdit4("Quad Color", &m_SquareColor[0], ImGuiColorEditFlags_PickerHueWheel);
	ImGui::DragFloat2("Position", &m_SquarePosition[0], 0.01f);
	ImGui::DragFloat("Rotation", &m_SquareRotation, 0.5f);
	ImGui::DragFloat2("Size", &m_SquareSize[0], 0.01f);
	ImGui::End();
}

void Sandbox2D::OnEvent(Maple::Event& event) {
	m_CameraController.OnEvent(event);
}
