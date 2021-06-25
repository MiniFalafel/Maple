#include <Maple.h>

#include "imgui/imgui.h"

class ExampleLayer : public Maple::Layer {

public:
	// TODO: Setup automatic aspect ratio!
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
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
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
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

uniform mat4 uViewProjectionMatrix;

out vec3 Pos;
out vec4 Color;

void main() {
	Pos = aPos;
	Color = aColor;
	gl_Position = uViewProjectionMatrix * vec4(Pos, 1.0);
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

uniform mat4 uViewProjectionMatrix;

out vec3 Pos;

void main() {
	Pos = aPos;
	gl_Position = uViewProjectionMatrix * vec4(Pos, 1.0);
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

	void OnUpdate(Maple::Timestep ts) {

		MP_INFO("Delta Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		// Update camera
		if (Maple::Input::IsKeyPressed(MP_KEY_A))
			m_Camera.AddToPosition(-m_CameraSpeed * ts * m_Camera.GetRightVector());
		if (Maple::Input::IsKeyPressed(MP_KEY_D))
			m_Camera.AddToPosition( m_CameraSpeed * ts * m_Camera.GetRightVector());
		if (Maple::Input::IsKeyPressed(MP_KEY_W))
			m_Camera.AddToPosition( m_CameraSpeed * ts * m_Camera.GetUpVector());
		if (Maple::Input::IsKeyPressed(MP_KEY_S))
			m_Camera.AddToPosition(-m_CameraSpeed * ts * m_Camera.GetUpVector());

		if (Maple::Input::IsKeyPressed(MP_KEY_Q))
			m_Camera.AddToRotation( ts * m_CameraRotationSpeed);
		if (Maple::Input::IsKeyPressed(MP_KEY_E))
			m_Camera.AddToRotation(-ts * m_CameraRotationSpeed);

		Maple::RenderCommand::SetClearColor({ 0.07f, 0.08f, 0.1f, 1.0f });
		Maple::RenderCommand::Clear();

		//m_Camera.SetPosition(m_CameraPosition);
		//m_Camera.SetRotation(180.0f);

		Maple::Renderer::BeginScene(m_Camera);
		{
			Maple::Renderer::Submit(m_SquareShader, m_SquareVAO);
			Maple::Renderer::Submit(m_Shader, m_VAO);
		}
		Maple::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Maple::Event& event) override {
		Maple::EventDispatcher dispatcher(event);
		// Set window resize function
		dispatcher.Dispatch<Maple::WindowResizeEvent>(MP_BIND_EVENT_FN(ExampleLayer::OnWindowResize));
	}

	bool OnWindowResize(Maple::WindowResizeEvent& event) {
		Maple::WindowResizeEvent& e = (Maple::WindowResizeEvent&)event;
		Maple::RenderCommand::SetViewPort(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	private:
		// Shaders
		std::shared_ptr<Maple::Shader> m_Shader;
		std::shared_ptr<Maple::Shader> m_SquareShader;

		// Vertex Arrays
		std::shared_ptr<Maple::VertexArray> m_VAO;
		std::shared_ptr<Maple::VertexArray> m_SquareVAO;

		// Camera
		Maple::OrthographicCamera m_Camera;
		// Camera movement and rotation speeds
		float m_CameraSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
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