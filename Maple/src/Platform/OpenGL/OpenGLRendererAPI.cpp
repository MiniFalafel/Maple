#include "mppch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Maple {

	void OpenGLRendererAPI::Init() {
		MP_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) {
		glViewport(x, y, X, Y);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VAO) {
		glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}