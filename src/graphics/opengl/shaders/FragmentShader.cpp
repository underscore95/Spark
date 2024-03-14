#include "FragmentShader.h"
#include "ShaderUtils.h"

const std::string INJECT_SOURCE = R"(
        
    )";

Spark::Graphics::GL::FragmentShader::FragmentShader(const std::string& filePath) : Spark::Graphics::Shader(filePath)
{
	read(INJECT_SOURCE);
	compileShader(GL_FRAGMENT_SHADER, source, filePath, rendererId);

#ifndef NDEBUG
	if (rendererId == 0) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("OpenGL FragmentShader has id 0");
	}
#endif
}
