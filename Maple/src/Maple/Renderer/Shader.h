#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Maple {

	class Shader {

	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// Uniform setting
		virtual void setMat3(const std::string& name, const glm::mat3& value) const = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& value) const = 0;
		// Vectors
		virtual void setVec2(const std::string& name, const glm::vec2& value) const = 0;
		virtual void setVec3(const std::string& name, const glm::vec3& value) const = 0;
		virtual void setVec4(const std::string& name, const glm::vec4& value) const = 0;
		// Float, Int, and Bool
		virtual void setFloat(const std::string& name, const float& value) const = 0;
		virtual void setInt(const std::string& name, const int& value) const = 0;
		virtual void setBool(const std::string& name, const bool& value) const = 0;

		static Shader* Create(std::string vertexSrc, std::string fragmentSrc);
	};

}