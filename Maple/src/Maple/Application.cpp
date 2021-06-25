#include "mppch.h"
#include "Application.h"

#include "Maple/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Maple {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		// Set s_Instance to this for external acces
		MP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(MP_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VAO.reset(VertexArray::Create());

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> m_VBO;
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::fVec3, "aPos" },
			{ ShaderDataType::fVec4, "aColor" }
		};
		m_VBO->SetLayout(layout);
		m_VAO->AddVertexBuffer(m_VBO);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> m_EBO;
		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VAO->SetIndexBuffer(m_EBO);

		// Square setup
		m_SquareVAO.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVBO;
		squareVBO.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVBO->SetLayout({
			{ ShaderDataType::fVec3, "aPos" }
		});
		m_SquareVAO->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1, 2, // Bottom tri
			0, 2, 3  // Top tri
		};
		std::shared_ptr<IndexBuffer> squareEBO;
		squareEBO.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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
		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		m_SquareShader.reset(Shader::Create(squareVertexSrc, squareFragmentSrc));
	}

	Application::~Application() {

	}

	// Layer and Overlay Handling Wrappers
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MP_BIND_EVENT_FN(Application::OnWindowClose));

		// Loop through each layer to see if it can handle the event
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(0.07f, 0.08f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Quad
			m_SquareShader->Bind();
			m_SquareVAO->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_SquareVAO->Unbind();

			// Triangle
			m_Shader->Bind();
			m_VAO->Bind();
			glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_VAO->Unbind();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}