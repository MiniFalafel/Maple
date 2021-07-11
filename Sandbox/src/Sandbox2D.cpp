#include "Sandbox2D.h"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach() {
	
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
		Maple::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
	}
	Maple::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Material Settings");
	ImGui::ColorEdit4("Material Color", &m_SquareColor[0], ImGuiColorEditFlags_PickerHueWheel);
	ImGui::End();
}

void Sandbox2D::OnEvent(Maple::Event& event) {
	m_CameraController.OnEvent(event);
}
