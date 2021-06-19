#include "Application.h"

#include "Maple/Events/ApplicationEvent.h"
#include "Maple/Log.h"

namespace Maple {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		MP_TRACE(e);

		while (true);
	}
}