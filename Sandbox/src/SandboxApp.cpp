#include <Maple.h>
#include <Maple/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.cpp"

class Sandbox : public Maple::Application {

public:

	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {
		
	}

};

Maple::Application* Maple::CreateApplication() {
	return new Sandbox();
}