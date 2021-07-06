#pragma once

#include <string>

namespace Maple {

	class Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Shader> Create(std::string vertexSrc, std::string fragmentSrc);
	};

}