#include "ShaderProgram.h"
#include <GL/glew.h>
#include "logging/Logger.h"
#include "logging/Logging.h"

Spark::Graphics::GL::ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) {
	rendererId = glCreateProgram();
	for (const auto& shader : shaders) {
		glAttachShader(rendererId, shader.getRendererId());
	}

	glLinkProgram(rendererId);
	glValidateProgram(rendererId);

	for (const auto& shader : shaders) {
		glDeleteShader(shader.getRendererId());
	}
}

Spark::Graphics::GL::ShaderProgram::~ShaderProgram() {
	glDeleteProgram(rendererId);
}

const int Spark::Graphics::GL::ShaderProgram::getUniformLocation(const std::string& variableName)
{
	if (cachedUniformLocations.find(variableName) != cachedUniformLocations.end()) {
		return cachedUniformLocations[variableName];
	}

	int location = glGetUniformLocation(rendererId, variableName.c_str());
	cachedUniformLocations.insert({ variableName, location });

	if (location == -1) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("No uniform with location " + variableName + " found in program.");
	}
	return location;
}

void Spark::Graphics::GL::ShaderProgram::bind() const
{
	glUseProgram(rendererId);
}

void Spark::Graphics::GL::ShaderProgram::unbind() const
{
	glUseProgram(0);
}

void Spark::Graphics::GL::ShaderProgram::setUniform2f(const std::string name, float v0, float v1)
{
	glUniform2f(getUniformLocation(name), v0, v1);
}

void Spark::Graphics::GL::ShaderProgram::setUniform1i(const std::string name, int i0)
{
	glUniform1i(getUniformLocation(name), i0);
}

void Spark::Graphics::GL::ShaderProgram::setUniformMat4f(const std::string name, const glm::mat4& m0)
{
	const size_t MATRIX_COUNT = 1;
	const bool REQUIRES_TRANSPOSE = GL_FALSE;
	glUniformMatrix4fv(getUniformLocation(name), MATRIX_COUNT, REQUIRES_TRANSPOSE, &m0[0][0]);
}
