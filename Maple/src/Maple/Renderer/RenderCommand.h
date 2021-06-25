#pragma once

#include "RendererAPI.h"

namespace Maple {

	class RenderCommand {

	public:
		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear() {
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& VAO) {
			s_RendererAPI->DrawIndexed(VAO);
		}

	private:
		static RendererAPI* s_RendererAPI;

	};

}