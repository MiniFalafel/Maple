#pragma once

#include "Maple/Renderer/RendererAPI.h"

namespace Maple {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void SetViewport(const int x, const int y, const int X, const int Y) override;

		virtual void DrawIndexed(const Ref<VertexArray>& VAO) override;


	};

}