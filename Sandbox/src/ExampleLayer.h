#pragma once
#include <Maple.h>
#include <imgui/imgui.h>

class ExampleLayer : public Maple::Layer {

public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(Maple::Timestep ts) override;

	virtual void OnImGuiRender() override;

	void OnEvent(Maple::Event& event) override;

private:
	// Shaders
	Maple::ShaderLibrary m_ShaderLibrary;
	Maple::Ref<Maple::Shader> m_FlatColorShader;

	// Textures
	Maple::Ref<Maple::Texture2D> m_CheckerTex, m_AwesomeFaceTex;

	// Vertex Arrays
	Maple::Ref<Maple::VertexArray> m_SquareVAO;

	// Camera
	Maple::OrthographicCameraController m_CameraController;

	// Colors
	glm::vec3 m_SquareColor = glm::vec3(0.8f, 0.2f, 0.3f);
};
