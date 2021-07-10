#include "mppch.h"
#include "VertexArray.h"

#include "Maple/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Maple {

	

	Ref <VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				MP_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}

		MP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}