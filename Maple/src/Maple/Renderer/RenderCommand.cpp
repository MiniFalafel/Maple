#include "mppch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Maple {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}