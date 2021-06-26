#include "mppch.h"
#include "Renderer.h"

namespace Maple {
	
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO, const glm::mat4& transform) {
		shader->Bind();
		shader->setMat4("uViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);
		shader->setMat4("uModelMatrix", transform);

		VAO->Bind();
		RenderCommand::DrawIndexed(VAO);
	}

}