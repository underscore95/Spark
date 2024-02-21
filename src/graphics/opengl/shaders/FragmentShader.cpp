#include "FragmentShader.h"
#include "ShaderUtils.h"

Spark::Graphics::GL::FragmentShader::FragmentShader(const std::string& filePath) : Spark::Graphics::Shader(filePath)
{
	read();
	compileShader(GL_FRAGMENT_SHADER, source, filePath, rendererId);
}