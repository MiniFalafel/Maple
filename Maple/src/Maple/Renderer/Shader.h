#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Maple {

	class Shader {

	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// Uniform setting
		virtual void setMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
		// Vectors
		virtual void setVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void setVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setVec4(const std::string& name, const glm::vec4& value) = 0;
		// Float, Int, and Bool
		virtual void setFloat(const std::string& name, const float& value) = 0;
		virtual void setInt(const std::string& name, const int& value) = 0;
		virtual void setBool(const std::string& name, const bool& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	};

	class ShaderLibrary {

	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& shaderName, const std::string& filePath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};

}