#pragma once

#include "RendererAPI.h"

namespace Maple {

	class RenderCommand {

	public:
		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }
		
		inline static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t X, const uint32_t Y) { s_RendererAPI->SetViewport(x, y, X, Y); }

		inline static void DrawIndexed(const Ref<VertexArray>& VAO) {
			s_RendererAPI->DrawIndexed(VAO);
		}

	private:
		static RendererAPI* s_RendererAPI;

	};

}