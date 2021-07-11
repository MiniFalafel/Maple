#pragma once

#include "Maple/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: Definitely remove this at some point because this is kind of ridiculous!
typedef unsigned int GLenum;

namespace Maple {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual const std::string& GetName() const override { return m_Name; }

		// Uniform setting
		virtual void setMat3(const std::string& name, const glm::mat3& value) override;
		virtual void setMat4(const std::string& name, const glm::mat4& value) override;
		// Vectors
		virtual void setVec2(const std::string& name, const glm::vec2& value) override;
		virtual void setVec3(const std::string& name, const glm::vec3& value) override;
		virtual void setVec4(const std::string& name, const glm::vec4& value) override;
		// Float, Int, and Bool
		virtual void setFloat(const std::string& name, const float& value) override;
		virtual void setInt(const std::string& name, const int& value) override;
		virtual void setBool(const std::string& name, const bool& value) override;

		// Uniform uploading
		virtual void uploadMat3(const std::string& name, const glm::mat3& value) const;
		virtual void uploadMat4(const std::string& name, const glm::mat4& value) const;
		
		virtual void uploadVec2(const std::string& name, const glm::vec2& value) const;
		virtual void uploadVec3(const std::string& name, const glm::vec3& value) const;
		virtual void uploadVec4(const std::string& name, const glm::vec4& value) const;
		
		virtual void uploadFloat(const std::string& name, const float& value) const;
		virtual void uploadInt(const std::string& name, const int& value) const;

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_ProgramID;
		std::string m_Name;
	};

}