#include "FragmentShader.h"
#include "ShaderUtils.h"

void Spark::Graphics::GL::FragmentShader::compile()
{
	compileShader(GL_FRAGMENT_SHADER, source, filePath, rendererId);
}
