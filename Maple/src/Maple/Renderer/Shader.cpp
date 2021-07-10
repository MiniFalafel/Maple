#include "mppch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Maple {
	Ref<Shader> Shader::Create(const std::string& filePath) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				MP_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(filePath);
		}

		MP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				MP_CORE_ASSERT(false, "RendererAPI::None is not currently supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		MP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// ShaderLibrary
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		MP_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath) {
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& shaderName, const std::string& filePath) {
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		MP_CORE_ASSERT(Exists(name), "Shader doesn't exist!");
		return m_Shaders[name];
	}
	
	bool ShaderLibrary::Exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}
}