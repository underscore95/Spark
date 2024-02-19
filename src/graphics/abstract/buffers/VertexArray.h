#pragma once

#include "pch.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Spark::Graphics {
	/*
	* This class is a container for a VertexBuffer, IndexBuffer, and a VertexBufferLayout.
	* This may be implemented using an Vertex Array Object (OpenGL) or via other means.
	*/
	class VertexArray {
	private:
		std::shared_ptr<IndexBuffer> indexBuffer;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<VertexBufferLayout> vertexBufferLayout;

	public:
		/*
		* \param indexBuffer The index buffer
		* \param vertexBuffer The vertex buffer
		* \param vertexBufferLayout The vertex buffer layout
		*/
		VertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<VertexBufferLayout>& vertexBufferLayout)
			: indexBuffer(indexBuffer), vertexBuffer(vertexBuffer), vertexBufferLayout(vertexBufferLayout)
		{
		}

		virtual	void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const unsigned int getIndicesCount() const final {
			return indexBuffer->getCount();
		}
	};
}