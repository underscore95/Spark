#include "VertexArray.h"

#include <GL/glew.h>

namespace Spark::Graphics::GL {

	VertexArray::VertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<VertexBufferLayout>& vertexBufferLayout)
		: Spark::Graphics::VertexArray(indexBuffer, vertexBuffer, vertexBufferLayout) {
		glGenVertexArrays(1, &rendererId);
		bind();

		vertexBuffer->bind();

		// Define buffer layout
		const auto& elements = vertexBufferLayout->getElements();
		unsigned int offset = 0;
		for (int i = 0; i < elements.size(); ++i) {
			const auto& element = elements.at(i);
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, vertexBufferLayout->getStride(), (const void*)offset);
			offset += element.count * element.size;
		}

		indexBuffer->bind();
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &rendererId);
	}

	void VertexArray::bind() const {
		glBindVertexArray(rendererId);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}

}