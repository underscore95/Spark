#include "ShaderProgram.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>

const int ShaderProgram::getUniformLocation(const std::string& variableName)
{
	if (cachedUniformLocations.find(variableName) != cachedUniformLocations.end()) {
		return cachedUniformLocations[variableName];
	}

	int location = glGetUniformLocation(programId, variableName.c_str());
	cachedUniformLocations.insert({ variableName, location });

	if (location == -1) {
		spdlog::warn("No uniform with location {} found in program.", variableName);
	}
	return location;
}

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders)
{
	programId = glCreateProgram();
	for (const auto& shader : shaders) {
		glAttachShader(programId, shader.getShaderId());
	}

	glLinkProgram(programId);
	glValidateProgram(programId);

	for (const auto& shader : shaders) {
		glDeleteShader(shader.getShaderId());
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
}

const unsigned int ShaderProgram::getId() const
{
	return programId;
}

void ShaderProgram::unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::bind() const
{
	glUseProgram(programId);
}

void ShaderProgram::setUniform2f(const std::string name, float v0, float v1)
{
	glUniform2f(getUniformLocation(name), v0, v1);
}

void ShaderProgram::setUniform1i(const std::string name, int i0)
{
	glUniform1i(getUniformLocation(name), i0);
}

void ShaderProgram::setUniformMat4f(const std::string name, const glm::mat4& m0)
{
	const size_t MATRIX_COUNT = 1;
	const bool REQUIRES_TRANSPOSE = GL_FALSE;
	glUniformMatrix4fv(getUniformLocation(name), MATRIX_COUNT, REQUIRES_TRANSPOSE, &m0[0][0]);
}
