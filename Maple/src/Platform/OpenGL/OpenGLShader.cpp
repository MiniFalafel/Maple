#include "mppch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Maple {

	OpenGLShader::OpenGLShader(std::string vertexSrc, std::string fragmentSrc) {
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			MP_CORE_ERROR("    {0}", infoLog.data());
			MP_CORE_ASSERT(false, "Vertex shader failed to compile!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			MP_CORE_ERROR("    {0}", infoLog.data());
			MP_CORE_ASSERT(false, "Fragment shader failed to compile!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ProgramID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_ProgramID, vertexShader);
		glAttachShader(m_ProgramID, fragmentShader);

		// Link our program
		glLinkProgram(m_ProgramID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_ProgramID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			MP_CORE_ERROR("    {0}", infoLog.data());
			MP_CORE_ASSERT(false, "Shader failed to link!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_ProgramID, vertexShader);
		glDetachShader(m_ProgramID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ProgramID);

	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_ProgramID);
	}
	
	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	// Uniforms
	// Matrices
	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
	}
	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
	// Vectors
	void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform2f(location, value[0], value[1]);
	}
	void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform3f(location, value[0], value[1], value[2]);
	}
	void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}
	// Float, Int, and Bool
	void OpenGLShader::setFloat(const std::string& name, const float& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::setInt(const std::string& name, const int& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::setBool(const std::string& name, const bool& value) const {
		GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
		glUniform1i(location, value);
	}

}