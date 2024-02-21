#pragma once

#include "pch.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Spark::Graphics {
	/*
	* This class is a container for a VertexBuffer, IndexBuffer, and a VertexBufferLayout.
	*/
	class VertexArray {
	protected:
		std::unique_ptr<IndexBuffer> indexBuffer;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		std::unique_ptr<VertexBufferLayout> vertexBufferLayout;

		virtual void init() { assert("Missing vertex array init implementation."); };
	public:
		/*
		* \param indexBuffer The index buffer
		* \param vertexBuffer The vertex buffer
		* \param vertexBufferLayout The vertex buffer layout
		*/
		VertexArray(std::unique_ptr<Spark::Graphics::IndexBuffer> indexBuffer,
			std::unique_ptr<Spark::Graphics::VertexBuffer> vertexBuffer,
			std::unique_ptr<Spark::Graphics::VertexBufferLayout> vertexBufferLayout)
			: indexBuffer{ std::move(indexBuffer) }, vertexBuffer{ std::move(vertexBuffer) }, vertexBufferLayout{ std::move(vertexBufferLayout) }
		{
			init();
		}

		virtual	void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const unsigned int getIndicesCount() const final {
			return indexBuffer->getCount();
		}
	};
}