#include "FragmentShader.h"
#include "ShaderUtils.h"

Spark::Graphics::GL::FragmentShader::FragmentShader(const std::string& filePath) : Spark::Graphics::Shader(filePath)
{
	read();
	compileShader(GL_FRAGMENT_SHADER, source, filePath, rendererId);

#ifndef NDEBUG
	if (rendererId == 0) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("OpenGL FragmentShader has id 0");
	}
#endif
}
