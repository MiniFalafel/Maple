#include "mppch.h"
#include "Application.h"

#include "Maple/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Maple {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::fVec2:    return GL_FLOAT;
			case ShaderDataType::fVec3:    return GL_FLOAT;
			case ShaderDataType::fVec4:    return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::iVec2:    return GL_INT;
			case ShaderDataType::iVec3:    return GL_INT;
			case ShaderDataType::iVec4:    return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}
	}

	Application::Application() {
		// Set s_Instance to this for external acces
		MP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(MP_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::fVec3, "aPos" },
			{ ShaderDataType::fVec4, "aColor" },
		};

		m_VBO->SetLayout(layout);

		uint32_t index = 0;
		for(const auto & e : m_VBO->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				e.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(e.Type),
				e.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)e.Offset
			);
			index++;
		}

		uint32_t indices[3] = { 0, 1, 2 };
		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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
	FragColor = vec4(Color);
}
)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
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
			glClearColor(0.09f, 0.09f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_EBO->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_Shader->Unbind();

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