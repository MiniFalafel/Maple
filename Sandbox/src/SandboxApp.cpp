#include <Maple.h>

#include "imgui/imgui.h"

class ExampleLayer : public Maple::Layer {

public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() {

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Maple::Event& event) override {
		// Check for the space bar and say "Jump"
		if (event.GetEventType() == Maple::EventType::KeyPressed) {
			Maple::KeyPressedEvent& e = (Maple::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MP_KEY_SPACE)
				MP_TRACE("Jump!");
		}
	}

};

class Sandbox : public Maple::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
		
	}

};

Maple::Application* Maple::CreateApplication() {
	return new Sandbox();
}