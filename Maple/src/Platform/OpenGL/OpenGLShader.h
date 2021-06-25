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

		virtual void setMat4(const std::string& name, const glm::mat4& value) const;

	private:
		uint32_t m_ProgramID;
	};

}