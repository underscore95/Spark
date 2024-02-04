#include "VertexArray.h"

int GL::VertexArray::switchToThisVAO()
{
	int vao;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
	bind();
	return vao;
}

GL::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

GL::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void GL::VertexArray::addVertexBuffer(const GL::VertexBuffer& buffer, const GL::BufferLayout& layout)
{
	int vao = switchToThisVAO();

	buffer.bind();

	// Define buffer layout
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); ++i) {
		const auto& element = elements.at(i);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset);
		offset += element.count * element.size;
	}

	glBindVertexArray(vao);
}

void GL::VertexArray::addIndexBuffer(const GL::IndexBuffer& buffer)
{
	int vao = switchToThisVAO();

	buffer.bind();
	indicesCount = buffer.getCount();

	glBindVertexArray(vao);
}

void GL::VertexArray::bind() const
{
	glBindVertexArray(id);
}

void GL::VertexArray::unbind() const
{
	glBindVertexArray(0);
}
