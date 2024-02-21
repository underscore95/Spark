#include "VertexBuffer.h"
#include <GL/glew.h>
#include "logging/Logger.h"
#include "logging/Logging.h"

Spark::Graphics::GL::VertexBuffer::VertexBuffer(unsigned int size, const void* data) : Spark::Graphics::VertexBuffer(size, data)
{
	glGenBuffers(1, &rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

#ifndef NDEBUG
	if (rendererId == 0) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("OpenGL ShaderProgram has id 0");
	}
#endif
}

Spark::Graphics::GL::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererId);
	Buffer::~Buffer();
}

void Spark::Graphics::GL::VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void Spark::Graphics::GL::VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
