#include "VertexShader.h"
#include "ShaderUtils.h"

void Spark::Graphics::GL::VertexShader::compile()
{
	compileShader(GL_VERTEX_SHADER, source, filePath, rendererId);
}
