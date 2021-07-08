#include <Maple.h>

#include "imgui/imgui.h"

class ExampleLayer : public Maple::Layer {

public:
	// TODO: Setup automatic aspect ratio!
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		
		// Square mesh
		m_SquareVAO.reset(Maple::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Maple::Ref<Maple::VertexBuffer> squareVBO;
		squareVBO = Maple::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVBO->SetLayout({
			{ Maple::ShaderDataType::fVec3, "aPos" },
			{ Maple::ShaderDataType::fVec2, "aTexCoords" }
		});
		m_SquareVAO->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1, 2, // Bottom tri
			0, 2, 3  // Top tri
		};
		Maple::Ref<Maple::IndexBuffer> squareEBO;
		squareEBO = Maple::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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
		m_FlatColorShader = Maple::Shader::Create(squareVertexSrc, squareFragmentSrc);
		// ************************************
		// *         Texture Shader           *
		// ************************************
		m_TextureShader = Maple::Shader::Create("assets/shaders/Texture.glsl");

		// Setup textures
		m_CheckerTex = Maple::Texture2D::Create("assets/textures/checker.png");
		m_AwesomeFaceTex = Maple::Texture2D::Create("assets/textures/awesomeface.png");
	}

	void OnUpdate(Maple::Timestep ts) {

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

		// Square transform
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		Maple::RenderCommand::SetClearColor({ 0.07f, 0.08f, 0.1f, 1.0f });
		Maple::RenderCommand::Clear();

		Maple::Renderer::BeginScene(m_Camera);
		{
			std::dynamic_pointer_cast<Maple::OpenGLShader>(m_FlatColorShader)->Bind();
			std::dynamic_pointer_cast<Maple::OpenGLShader>(m_FlatColorShader)->setVec3("uColor", m_SquareColor);

			for (int y = -10; y < 10; y++) {
				for (int x = -10; x < 10; x++) {
					glm::vec3 offsetPos((float)x * 0.11f, (float)y * 0.11f, 0.0f);
					glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), offsetPos) * scale;
					Maple::Renderer::Submit(m_FlatColorShader, m_SquareVAO, squareTransform);
				}
			}

			// Large Textured Quads
			// Shader uniforms
			std::dynamic_pointer_cast<Maple::OpenGLShader>(m_TextureShader)->Bind();
			std::dynamic_pointer_cast<Maple::OpenGLShader>(m_TextureShader)->setInt("uTexImage", 0);
			// Checker quad
			m_CheckerTex->Bind(0);
			// Submit it for rendering
			Maple::Renderer::Submit(m_TextureShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			// Awesomeface quad
			m_AwesomeFaceTex->Bind(0);
			// Submit it for rendering
			Maple::Renderer::Submit(m_TextureShader, m_SquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		}
		Maple::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Material Settings");
		ImGui::ColorEdit3("Material Color", &m_SquareColor[0], ImGuiColorEditFlags_PickerHueWheel);
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
		Maple::Ref<Maple::Shader> m_FlatColorShader, m_TextureShader;

		// Textures
		Maple::Ref<Maple::Texture2D> m_CheckerTex, m_AwesomeFaceTex;

		// Vertex Arrays
		Maple::Ref<Maple::VertexArray> m_SquareVAO;

		// Camera
		Maple::OrthographicCamera m_Camera;
		// Camera movement and rotation speeds
		float m_CameraSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;

		// Colors
		glm::vec3 m_SquareColor = glm::vec3(0.8f, 0.2f, 0.3f);
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