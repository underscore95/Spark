#include "IndexBuffer.h"
#include <GL/glew.h>
#include "logging/Logger.h"
#include "logging/Logging.h"

Spark::Graphics::GL::IndexBuffer::IndexBuffer(unsigned int size, unsigned int count, const void* data) : Spark::Graphics::IndexBuffer(size, count, data)
{
	glGenBuffers(1, &rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

#ifndef NDEBUG
	if (rendererId == 0) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("OpenGL ShaderProgram has id 0");
	}
#endif
}

Spark::Graphics::GL::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererId);
	Buffer::~Buffer();
}

void Spark::Graphics::GL::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void Spark::Graphics::GL::IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
