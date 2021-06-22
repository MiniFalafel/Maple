#include <Maple.h>

class ExampleLayer : public Maple::Layer {

public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() {
		MP_INFO("ExampleLayer:: Updated");
	}

	void OnEvent(Maple::Event& event) override {
		MP_TRACE("{0}", event);
	}
};

class Sandbox : public Maple::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Maple::ImGuiLayer());
	}

	~Sandbox() {
		
	}

};

Maple::Application* Maple::CreateApplication() {
	return new Sandbox();
}