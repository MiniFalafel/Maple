#include "mppch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Maple {
	Shader* Shader::Create(std::string vertexSrc, std::string fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				MP_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);
		}
	}

}