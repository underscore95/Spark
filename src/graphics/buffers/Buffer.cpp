#include "Buffer.h"

GL::Buffer::Buffer(int type, int usageHint, unsigned int size, const void* data) : type{ type }, usageHint{ usageHint }, size{ size }, data{ data } {
	int vao;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
	glBindVertexArray(0);

	glGenBuffers(1, &id);
	glBindBuffer(type, id);
	glBufferData(type, size, data, usageHint);

	glBindVertexArray(vao);
}

GL::Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
	delete[] data;
}

const unsigned int GL::Buffer::getId() const
{
	return id;
}

void GL::Buffer::bind() const
{
	glBindBuffer(type, id);
}

void GL::Buffer::unbind() const
{
	glBindBuffer(type, 0);
}