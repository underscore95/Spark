#pragma once

#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"

namespace GL {
	class VertexArray {
	private:
		unsigned int id;
		unsigned int indicesCount{ 0 };

		// Returns id of previous vertex array
		int switchToThisVAO();
	public:
		VertexArray();
		~VertexArray();

		void addVertexBuffer(const GL::VertexBuffer& buffer, const GL::BufferLayout& layout);
		void addIndexBuffer(const GL::IndexBuffer& buffer);

		const unsigned int getAmountOfIndices() const { return indicesCount; }

		void bind() const;
		void unbind() const;
	};
}