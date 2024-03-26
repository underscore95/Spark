#include "VertexArray.h"

#include <GL/glew.h>

#include "logging/Logger.h"
#include "logging/Logging.h"

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

	VertexArray::VertexArray(std::shared_ptr<Spark::Graphics::IndexBuffer> indexBuffer,
		std::unique_ptr<Spark::Graphics::VertexBuffer> vertexBuffer,
		std::shared_ptr<Spark::Graphics::VertexBufferLayout> vertexBufferLayout)
		: Spark::Graphics::VertexArray(indexBuffer, std::move(vertexBuffer), vertexBufferLayout),
		rendererId{ 0 }
	{
		init();
#ifndef NDEBUG
		if (rendererId == 0) {
			auto& logger = SparkInternal::getLogger();
			logger.warning("VAO ID for OpenGL Vertex Array is 0");
		}
#endif
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