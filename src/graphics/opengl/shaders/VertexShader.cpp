#include "VertexShader.h"
#include "ShaderUtils.h"

void Spark::Graphics::GL::VertexShader::compile()
{
	compileShader(GL_VERTEX_SHADER, source, filePath, rendererId);
}

Spark::Graphics::GL::VertexShader::VertexShader(const std::string& filePath) : Spark::Graphics::Shader(filePath)
{
}
