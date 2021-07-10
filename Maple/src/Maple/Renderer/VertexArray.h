#pragma once

#include "Maple/Renderer/Buffer.h"

namespace Maple {
	
	class VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& VBO) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& EBO) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};

}
