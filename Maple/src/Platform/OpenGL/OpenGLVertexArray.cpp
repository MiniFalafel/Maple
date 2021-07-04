#include "mppch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Maple {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::fVec2:    return GL_FLOAT;
			case ShaderDataType::fVec3:    return GL_FLOAT;
			case ShaderDataType::fVec4:    return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::iVec2:    return GL_INT;
			case ShaderDataType::iVec3:    return GL_INT;
			case ShaderDataType::iVec4:    return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		MP_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_VertexArrayID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& VBO) {

		MP_CORE_ASSERT(VBO->GetLayout().GetElements().size(), "Vertex buffer layout is empty!");

		glBindVertexArray(m_VertexArrayID);
		VBO->Bind();

		uint32_t index = 0;
		const auto& layout = VBO->GetLayout();
		for (const auto& e : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				e.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(e.Type),
				e.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)e.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(VBO);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& EBO) {
		glBindVertexArray(m_VertexArrayID);
		EBO->Bind();

		m_IndexBuffer = EBO;
	}

}