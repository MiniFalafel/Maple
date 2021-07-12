#include "mppch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Maple {

	/******************************
	* OpenGL Vertex Buffer Start! *
	*******************************/

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		MP_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		MP_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_VertexBufferID);
	}

	void OpenGLVertexBuffer::Bind() const {
		MP_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		MP_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*****************************
	* OpenGL Index Buffer Start! *
	******************************/

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count) {
		MP_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_ElementBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		MP_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_ElementBufferID);
	}

	void OpenGLIndexBuffer::Bind() const {
		MP_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		MP_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}