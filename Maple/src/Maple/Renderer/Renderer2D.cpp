#include "mppch.h"
#include "Renderer2D.h"

#include "Maple/Renderer/Shader.h"
#include "Maple/Renderer/VertexArray.h"

#include "Maple/Renderer/RenderCommand.h"

namespace Maple {

	struct Renderer2DStorage {

		Ref<VertexArray> vertexArray;
		Ref<Shader> Shader;
		Ref<Texture> whiteTexture;

	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {

		s_Data = new Renderer2DStorage();
		s_Data->vertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> squareVBO;
		squareVBO = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVBO->SetLayout({
			{ ShaderDataType::fVec3, "aPos" },
			{ShaderDataType::fVec2, "aTexCoords"}
		});
		s_Data->vertexArray->AddVertexBuffer(squareVBO);

		uint32_t squareIndices[6] = {
			0, 1, 2, // Bottom tri
			0, 2, 3  // Top tri
		};
		Ref<IndexBuffer> squareEBO;
		squareEBO = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->vertexArray->SetIndexBuffer(squareEBO);

		s_Data->whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		
		s_Data->Shader = Shader::Create("assets/shaders/Main2D.glsl");
		s_Data->Shader->Bind();
		s_Data->Shader->setInt("uTexImage", 0);
		s_Data->Shader->setVec4("uColor", glm::vec4(1.0f));

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

		s_Data->Shader->setMat4("uModelMatrix", modelMatrix);
		s_Data->Shader->setVec4("uColor", color);
		s_Data->whiteTexture->Bind();

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);

	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({position.x, position.y, 0.0f}, rotation, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor) {
		
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->Shader->setMat4("uModelMatrix", modelMatrix);
		s_Data->Shader->setVec4("uColor", tintColor);

		texture->Bind();

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor) {
		DrawQuad({position.x, position.y, 0.0f}, rotation, size, texture, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const float& textureScale, const glm::vec4& tintColor) {

		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->Shader->setFloat("uTextureScale", textureScale);
		s_Data->Shader->setMat4("uModelMatrix", modelMatrix);
		s_Data->Shader->setVec4("uColor", tintColor);

		texture->Bind();

		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const float& textureScale, const glm::vec4& tintColor) {
		DrawQuad({ position.x, position.y, 0.0f }, rotation, size, texture, textureScale, tintColor);
	}

}