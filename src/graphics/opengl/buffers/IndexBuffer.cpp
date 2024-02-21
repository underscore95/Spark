#include "IndexBuffer.h"
#include <GL/glew.h>

Spark::Graphics::GL::IndexBuffer::IndexBuffer(unsigned int size, unsigned int count, const void* data) : Spark::Graphics::IndexBuffer(size, count, data)
{
	glGenBuffers(1, &rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	assert(rendererId != 0);
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
