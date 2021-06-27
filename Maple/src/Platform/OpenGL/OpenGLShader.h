#pragma once

#include "Maple/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Maple {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(std::string vertexSrc, std::string fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		// Uniform setting
		// Matrices
		virtual void setMat3(const std::string& name, const glm::mat3& value) const;
		virtual void setMat4(const std::string& name, const glm::mat4& value) const;
		// Vectors
		virtual void setVec2(const std::string& name, const glm::vec2& value) const;
		virtual void setVec3(const std::string& name, const glm::vec3& value) const;
		virtual void setVec4(const std::string& name, const glm::vec4& value) const;
		// Float, Int, and Bool
		virtual void setFloat(const std::string& name, const float& value) const;
		virtual void setInt(const std::string& name, const int& value) const;
		virtual void setBool(const std::string& name, const bool& value) const;

	private:
		uint32_t m_ProgramID;
	};

}