#pragma once

#ifndef MP_ENTRY_POINT
#define MP_ENTRY_POINT

#ifdef MP_PLATFORM_WINDOWS

extern Maple::Application* Maple::CreateApplication();

int main(int argc, char** argv) {
	
	Maple::Log::Init();
	MP_CORE_WARN("Initialized Log!");
	MP_INFO("Hello!");

	auto app = Maple::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif

#endif