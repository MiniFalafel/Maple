#include <Maple.h>
#include <imgui/imgui.h>
#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {

	// Square mesh
	m_SquareVAO = Maple::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	Maple::Ref<Maple::VertexBuffer> squareVBO = Maple::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVBO->SetLayout({
		{ Maple::ShaderDataType::fVec3, "aPos" },
		{ Maple::ShaderDataType::fVec2, "aTexCoords" }
		});
	m_SquareVAO->AddVertexBuffer(squareVBO);

	uint32_t squareIndices[6] = {
		0, 1, 2, // Bottom tri
		0, 2, 3  // Top tri
	};
	Maple::Ref<Maple::IndexBuffer> squareEBO = Maple::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVAO->SetIndexBuffer(squareEBO);

	// ************************************
	// *        Flat Color Shader         *
	// ************************************
	std::string squareVertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 uViewProjectionMatrix;
uniform mat4 uModelMatrix;

void main() {
	vec3 Pos = vec3(uModelMatrix * vec4(aPos, 1.0));
	gl_Position = uViewProjectionMatrix * vec4(Pos, 1.0);
}
		)";
	std::string squareFragmentSrc = R"(
#version 330 core
layout(location = 0) out vec4 FragColor;

uniform vec3 uColor;

void main() {
	FragColor = vec4(uColor, 1.0);
}
)";
	m_FlatColorShader = Maple::Shader::Create("FlatColor", squareVertexSrc, squareFragmentSrc);
	// ************************************
	// *         Texture Shader           *
	// ************************************
	auto TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	// Setup textures
	m_CheckerTex = Maple::Texture2D::Create("assets/textures/checker.png");
	m_AwesomeFaceTex = Maple::Texture2D::Create("assets/textures/awesomeface.png");

	// Set Texture bindings
	TextureShader->Bind();
	TextureShader->setInt("uTexImage", 0);
}

void ExampleLayer::OnUpdate(Maple::Timestep ts) {

	// Update camera
	m_CameraController.OnUpdate(ts);

	// Render
	Maple::RenderCommand::SetClearColor({ 0.07f, 0.08f, 0.1f, 1.0f });
	Maple::RenderCommand::Clear();

	Maple::Renderer::BeginScene(m_CameraController.GetCamera());
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->setVec3("uColor", m_SquareColor);

		for (int y = -10; y < 10; y++) {
			for (int x = -10; x < 10; x++) {
				glm::vec3 offsetPos((float)x * 0.11f, (float)y * 0.11f, 0.0f);
				glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), offsetPos) * scale;
				Maple::Renderer::Submit(m_FlatColorShader, m_SquareVAO, squareTransform);
			}
		}

		// Large Textured Quads
		// Get Shader
		auto textureShader = m_ShaderLibrary.Get("Texture");
		// Checker quad
		m_CheckerTex->Bind(0);
		// Submit it for rendering
		Maple::Renderer::Submit(textureShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Awesomeface quad
		m_AwesomeFaceTex->Bind(0);
		// Submit it for rendering
		Maple::Renderer::Submit(textureShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	}
	Maple::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender() {
	ImGui::Begin("Material Settings");
	ImGui::ColorEdit3("Material Color", &m_SquareColor[0], ImGuiColorEditFlags_PickerHueWheel);
	ImGui::End();
}

void ExampleLayer::OnEvent(Maple::Event& event) {
	// Camera events
	m_CameraController.OnEvent(event);
}
