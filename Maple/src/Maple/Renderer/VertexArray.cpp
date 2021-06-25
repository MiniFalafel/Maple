#include "mppch.h"
#include "VertexArray.h"

#include "Maple/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Maple {

	

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				MP_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		}

		MP_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}