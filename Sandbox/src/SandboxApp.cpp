#include <Maple.h>

#include "imgui/imgui.h"

class ExampleLayer : public Maple::Layer {

public:
	ExampleLayer() : Layer("Example") {
		m_VAO.reset(Maple::VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<Maple::VertexBuffer> m_VBO;
		m_VBO.reset(Maple::VertexBuffer::Create(vertices, sizeof(vertices)));
		Maple::BufferLayout layout = {
			{ Maple::ShaderDataType::fVec3, "aPos" },
			{ Maple::ShaderDataType::fVec4, "aColor" }
		};
		m_VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(m_VBO);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Maple::IndexBuffer> m_EBO;
		m_EBO.reset(Maple::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VAO->SetIndexBuffer(m_EBO);

		// Square setup
		m_SquareVAO.reset(Maple::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<Maple::VertexBuffer> squareVBO;
		squareVBO.reset(Maple::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVBO->SetLayout({
			{ Maple::ShaderDataType::fVec3, "aPos" }
			});
		m_SquareVAO->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1, 2, // Bottom tri
			0, 2, 3  // Top tri
		};
		std::shared_ptr<Maple::IndexBuffer> squareEBO;
		squareEBO.reset(Maple::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(squareEBO);

		std::string vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec3 Pos;
out vec4 Color;

void main() {
	Pos = aPos;
	Color = aColor;
	gl_Position = vec4(Pos, 1.0);
}
		)";
		std::string fragmentSrc = R"(
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 Pos;
in vec4 Color;

void main() {
	FragColor = vec4(Color.rgb, 1.0);
}
)";
		std::string squareVertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 Pos;
out vec4 Color;

void main() {
	Pos = aPos;
	gl_Position = vec4(1.5 * Pos, 1.0);
}
		)";
		std::string squareFragmentSrc = R"(
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec3 Pos;

void main() {
	FragColor = vec4(0.2, 0.2, 0.8, 1.0);
}
)";
		m_Shader.reset(Maple::Shader::Create(vertexSrc, fragmentSrc));
		m_SquareShader.reset(Maple::Shader::Create(squareVertexSrc, squareFragmentSrc));
	}

	void OnUpdate() {

		Maple::RenderCommand::SetClearColor({ 0.07f, 0.08f, 0.1f, 1.0f });
		Maple::RenderCommand::Clear();

		Maple::Renderer::BeginScene();
		{
			m_SquareShader->Bind();
			Maple::Renderer::Submit(m_SquareVAO);

			m_Shader->Bind();
			Maple::Renderer::Submit(m_VAO);
		}
		Maple::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Maple::Event& event) override {
		// Check for the space bar and say "Jump"
		if (event.GetEventType() == Maple::EventType::KeyPressed) {
			Maple::KeyPressedEvent& e = (Maple::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MP_KEY_SPACE)
				MP_TRACE("Jump!");
		}
	}

	private:
		// Shaders
		std::shared_ptr<Maple::Shader> m_Shader;
		std::shared_ptr<Maple::Shader> m_SquareShader;

		// Vertex Arrays
		std::shared_ptr<Maple::VertexArray> m_VAO;
		std::shared_ptr<Maple::VertexArray> m_SquareVAO;

};

class Sandbox : public Maple::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
		
	}

};

Maple::Application* Maple::CreateApplication() {
	return new Sandbox();
}