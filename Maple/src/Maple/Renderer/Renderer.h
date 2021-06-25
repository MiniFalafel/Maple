#pragma once

#include "RenderCommand.h"

namespace Maple {
	
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& VAO);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}