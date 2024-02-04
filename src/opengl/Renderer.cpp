#include "Renderer.h"

void GL::Renderer::draw(const VertexArray& vertexArray, const ShaderProgram& shader)
{
	shader.bind();
	vertexArray.bind();

	glDrawElements(GL_TRIANGLES, vertexArray.getAmountOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GL::Renderer::clearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
