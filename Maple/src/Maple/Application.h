#pragma once

#include "Core.h"
#include "Window.h"

#include "Maple/LayerStack.h"
#include "Maple/Events/Event.h"
#include "Maple/Events/ApplicationEvent.h"

#include "Maple/Core/Timestep.h"

#include "Maple/ImGui/ImGuiLayer.h"

namespace Maple {

	class Application {

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
		float m_LastFrameTime = 0.0f;

		// Single instance of self for the "Get" function
		static Application* s_Instance;
	};

	// Will be client defined
	Application* CreateApplication();

}