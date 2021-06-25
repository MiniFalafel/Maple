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
		virtual void setMat4(const std::string& name, const glm::mat4& value) const = 0;

		static Shader* Create(std::string vertexSrc, std::string fragmentSrc);
	};

}