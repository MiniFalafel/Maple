#pragma once

#include <Maple.h>
#include <Maple/Renderer/Renderer2D.h>

class Sandbox2D : public Maple::Layer {

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Maple::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Maple::Event& event) override;

private:
	Maple::OrthographicCameraController m_CameraController;

	// Very temporary!
	Maple::Ref<Maple::VertexArray> m_SquareVAO;
	Maple::Ref<Maple::Shader> m_FlatColorShader;

	// ImGui Controllable Color
	glm::vec4 m_SquareColor = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);

};