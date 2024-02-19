#include "Renderer.h"
#include <GL/glew.h>

void Spark::Graphics::GL::Renderer::draw(const VertexArray& vertexArray, const ShaderProgram& shaders) const
{
	shaders.bind();
	vertexArray.bind();

	glDrawElements(GL_TRIANGLES, vertexArray.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void Spark::Graphics::GL::Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
