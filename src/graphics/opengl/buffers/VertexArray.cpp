#include "VertexArray.h"

#include <GL/glew.h>

namespace Spark::Graphics::GL {
	void VertexArray::init()
	{
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

	VertexArray::VertexArray(std::unique_ptr<Spark::Graphics::IndexBuffer> indexBuffer,
		std::unique_ptr<Spark::Graphics::VertexBuffer> vertexBuffer,
		std::unique_ptr<Spark::Graphics::VertexBufferLayout> vertexBufferLayout)
		: Spark::Graphics::VertexArray(std::move(indexBuffer), std::move(vertexBuffer), std::move(vertexBufferLayout))
	{}

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