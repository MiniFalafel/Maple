#include "mppch.h"
#include "Renderer.h"

namespace Maple {
	
	void Renderer::BeginScene() {

	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& VAO) {
		VAO->Bind();
		RenderCommand::DrawIndexed(VAO);
	}

}