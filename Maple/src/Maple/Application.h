#pragma once

#include "Core.h"
#include "Window.h"

#include "Maple/LayerStack.h"
#include "Maple/Events/Event.h"
#include "Maple/Events/ApplicationEvent.h"

namespace Maple {

	class MAPLE_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Will be client defined
	Application* CreateApplication();

}