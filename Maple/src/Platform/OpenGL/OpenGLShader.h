#pragma once
#include "OpenGLShader.h"

#include "Maple/Renderer/Shader.h"

namespace Maple {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(std::string vertexSrc, std::string fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

	private:
		uint32_t m_ProgramID;
	};

}