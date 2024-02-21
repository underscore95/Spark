#include "VertexBuffer.h"
#include <GL/glew.h>

Spark::Graphics::GL::VertexBuffer::VertexBuffer(unsigned int size, const void* data) : Spark::Graphics::VertexBuffer(size, data)
{
	glGenBuffers(1, &rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	assert(rendererId != 0);
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
