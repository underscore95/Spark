#include "VertexShader.h"
#include "ShaderUtils.h"
#include "pch.h"

void Spark::Graphics::GL::VertexShader::injectShaderCode()
{
	
}

Spark::Graphics::GL::VertexShader::VertexShader(const std::string& filePath) : Spark::Graphics::Shader(filePath)
{
	read();
	injectShaderCode();
	compileShader(GL_VERTEX_SHADER, source, filePath, rendererId);

#ifndef NDEBUG
	if (rendererId == 0) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("OpenGL FragmentShader has id 0");
	}
#endif
}
