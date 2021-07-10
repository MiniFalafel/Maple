#include "Sandbox2D.h"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach() {
	// Square mesh
	m_SquareVAO = Maple::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	Maple::Ref<Maple::VertexBuffer> squareVBO;
	squareVBO = Maple::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVBO->SetLayout({
		{ Maple::ShaderDataType::fVec3, "aPos" }
	});
	m_SquareVAO->AddVertexBuffer(squareVBO);

	uint32_t squareIndices[6] = {
		0, 1, 2, // Bottom tri
		0, 2, 3  // Top tri
	};
	Maple::Ref<Maple::IndexBuffer> squareEBO;
	squareEBO = Maple::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVAO->SetIndexBuffer(squareEBO);

	m_FlatColorShader = Maple::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Maple::Timestep ts) {
	// Update camera
	m_CameraController.OnUpdate(ts);

	// Render
	Maple::RenderCommand::SetClearColor({ 0.07f, 0.08f, 0.1f, 1.0f });
	Maple::RenderCommand::Clear();

	Maple::Renderer::BeginScene(m_CameraController.GetCamera());
	{
		std::dynamic_pointer_cast<Maple::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Maple::OpenGLShader>(m_FlatColorShader)->setVec4("uColor", m_SquareColor);

		Maple::Renderer::Submit(m_FlatColorShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	}
	Maple::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Material Settings");
	ImGui::ColorEdit4("Material Color", &m_SquareColor[0], ImGuiColorEditFlags_PickerHueWheel);
	ImGui::End();
}

void Sandbox2D::OnEvent(Maple::Event& event) {
	m_CameraController.OnEvent(event);
}
