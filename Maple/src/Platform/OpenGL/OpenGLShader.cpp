#include "mppch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Maple {
	static GLenum ShaderTypeFromString(const std::string type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		MP_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath) {

		std::string source = ReadFile(filePath);
		auto shaderSources = Preprocess(source);
		Compile(shaderSources);
		
		// Get name from filepath
		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filePath.rfind(".");
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filePath.substr(lastSlash, count);
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name) {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ProgramID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath) {
		std::string result;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			MP_CORE_ERROR("Could not open file '{0}'", filePath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string source) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			MP_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			MP_CORE_ASSERT(ShaderTypeFromString(type) , "Shader type not supported!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		GLuint program = glCreateProgram();
		MP_CORE_ASSERT(shaderSources.size() <= 3, "There is a maximum of 3 shaders allowed");
		std::array<GLenum, 3> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources) {
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* cSource = source.c_str();
			glShaderSource(shader, 1, &cSource, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				MP_CORE_ERROR("    {0}", infoLog.data());
				MP_CORE_ASSERT(false, "Shader failed to compile!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}


		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto ID : glShaderIDs)
				glDeleteShader(ID);

			MP_CORE_ERROR("    {0}", infoLog.data());
			MP_CORE_ASSERT(false, "Shader failed to link!");
			return;
		}

		for (auto ID : glShaderIDs)
			glDetachShader(program, ID);

		m_ProgramID = program;
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_ProgramID);
	}
	
	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	// Uniform functions
	// Set functions
	// Matrices
	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& value) {
		uploadMat3(name, value);
	}
	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) {
		uploadMat4(name, value);
	}
	// Float vectors
	void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) {
		uploadVec2(name, value);
	}
	void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value) {
		uploadVec3(name, value);
	}
	void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value) {
		uploadVec4(name, value);
	}
	// Single value types
	void OpenGLShader::setFloat(const std::string& name, const float& value) {
		uploadFloat(name, value);
	}
	void OpenGLShader::setInt(const std::string& name, const int& value) {
		uploadInt(name, value);
	}
	void OpenGLShader::setBool(const std::string& name, const bool& value) {
		uploadInt(name, value);
	}

	// Upload functions
	// Matrices
	void OpenGLShader::uploadMat3(const std::string& name, const glm::mat3& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
	}
	void OpenGLShader::uploadMat4(const std::string& name, const glm::mat4& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
	// Vectors
	void OpenGLShader::uploadVec2(const std::string& name, const glm::vec2& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform2f(location, value[0], value[1]);
	}
	void OpenGLShader::uploadVec3(const std::string& name, const glm::vec3& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform3f(location, value[0], value[1], value[2]);
	}
	void OpenGLShader::uploadVec4(const std::string& name, const glm::vec4& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}
	// Float, Int, and Bool
	void OpenGLShader::uploadFloat(const std::string& name, const float& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::uploadInt(const std::string& name, const int& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1i(location, value);
	}

}