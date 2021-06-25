#pragma once

#include "Maple/Renderer/Buffer.h"

namespace Maple {
	
	class VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& EBO) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}
