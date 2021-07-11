#pragma once

#include "Maple/Renderer/Shader.h"
#include "Maple/Renderer/VertexArray.h"
#include "Maple/Renderer/OrthographicCamera.h"

#include "Maple/Renderer/RenderCommand.h"

namespace Maple {

	class Renderer2D {
		
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& size, const glm::vec4& color);

	};

}