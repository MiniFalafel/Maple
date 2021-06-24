#pragma once

#include "Core.h"
#include "Window.h"

#include "Maple/LayerStack.h"
#include "Maple/Events/Event.h"
#include "Maple/Events/ApplicationEvent.h"

#include "Maple/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

namespace Maple {

	class MAPLE_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VAO;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;

		// Single instance of self for the "Get" function
		static Application* s_Instance;
	};

	// Will be client defined
	Application* CreateApplication();

}