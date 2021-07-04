#include "mppch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Maple {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(const int x, const int y, const int X, const int Y) {
		glViewport(x, y, X, Y);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VAO) {
		glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}