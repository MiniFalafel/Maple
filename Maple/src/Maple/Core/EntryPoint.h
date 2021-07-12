#pragma once

#ifndef MP_ENTRY_POINT
#define MP_ENTRY_POINT

#ifdef MP_PLATFORM_WINDOWS

extern Maple::Application* Maple::CreateApplication();

int main(int argc, char** argv) {
	
	Maple::Log::Init();

	MP_PROFILE_BEGIN_SESSION("Startup", "MapleProfile-Startup.json");
	auto app = Maple::CreateApplication();
	MP_PROFILE_END_SESSION();

	MP_PROFILE_BEGIN_SESSION("Runtime", "MapleProfile-Runtime.json");
	app->Run();
	MP_PROFILE_END_SESSION();

	MP_PROFILE_BEGIN_SESSION("Shutdown", "MapleProfile-Shutdown.json");
	delete app;
	MP_PROFILE_END_SESSION();

	return 0;
}

#endif

#endif