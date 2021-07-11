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

	// ImGui Controllable Variables
	glm::vec4 m_SquareColor = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);
	glm::vec2 m_SquarePosition = glm::vec2(0.25f, -0.25f);
	glm::vec2 m_SquareSize = glm::vec2(0.5f, 0.5f);

	float m_SquareRotation = 0.0f;

	// Textures
	Maple::Ref<Maple::Texture2D> m_CheckerTex;

};