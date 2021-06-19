#pragma once

#ifdef MP_PLATFORM_WINDOWS

extern Maple::Application* Maple::CreateApplication();

int main(int argc, char** argv) {
	
	Maple::Log::Init();
	MP_CORE_WARN("Initialized Log!");
	int a = 5;
	MP_INFO("Hello! Var={0}", a);

	auto app = Maple::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif