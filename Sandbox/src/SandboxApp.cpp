#include <Maple.h>

class Sandbox : public Maple::Application {

public:

	Sandbox() {
		
	}

	~Sandbox() {
		
	}

};

Maple::Application* Maple::CreateApplication() {
	return new Sandbox();
}