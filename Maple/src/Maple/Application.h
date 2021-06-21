#pragma once

#include "Core.h"
#include "Window.h"

#include "Maple/Events/Event.h"
#include "Maple/Events/ApplicationEvent.h"

namespace Maple {

	class MAPLE_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);



	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// Will be client defined
	Application* CreateApplication();

}