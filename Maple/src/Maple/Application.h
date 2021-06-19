#pragma once

#include "Core.h"
#include "Events/event.h"

namespace Maple {
	class MAPLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Will be client defined
	Application* CreateApplication();
}