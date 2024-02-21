#include "VertexBufferLayout.h"
#include <GL/glew.h>

void Spark::Graphics::GL::VertexBufferLayout::pushFloat(unsigned int count)
{
	push(sizeof(float), count, GL_FLOAT);
}
