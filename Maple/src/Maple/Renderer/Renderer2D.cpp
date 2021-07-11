#include "mppch.h"
#include "Renderer2D.h"

namespace Maple {

	struct Renderer2DStorage {

		Ref<VertexArray> vertexArray;
		Ref<Shader> Shader;

	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {

		s_Data = new Renderer2DStorage();
		s_Data->vertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		Ref<VertexBuffer> squareVBO;
		squareVBO = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVBO->SetLayout({
			{ ShaderDataType::fVec3, "aPos" }
		});
		s_Data->vertexArray->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1, 2, // Bottom tri
			0, 2, 3  // Top tri
		};
		Ref<IndexBuffer> squareEBO;
		squareEBO = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->vertexArray->SetIndexBuffer(squareEBO);

		s_Data->Shader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->Shader->Bind();
		s_Data->Shader->setMat4("uViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene() {
		// Nothing for now
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const glm::vec4& color) {
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->Shader->Bind();
		s_Data->Shader->setMat4("uModelMatrix", modelMatrix);
		s_Data->Shader->setVec4("uColor", color);

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({position.x, position.y, 0.0f}, rotation, size, color);
	}

}