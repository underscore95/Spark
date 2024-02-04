#include "Shader.h"
#include <spdlog/spdlog.h>
#include <GL/glew.h>
#include <sstream>

Shader::Shader(const std::string& filePath, int shaderType) : filePath{ filePath }, type{ shaderType }
{
	readShaderFile();
	compileShader();
}

const unsigned int Shader::getShaderId() const
{
	return id;
}

void Shader::readShaderFile()
{
	std::string line;
	std::ifstream stream(filePath);

	if (!stream.is_open()) {
		spdlog::error("Failed to open file: ", filePath);
		return;
	}

	std::stringstream buffer;
	while (std::getline(stream, line)) {
		buffer << line << '\n';
	}
	source = buffer.str();
	stream.close();
}

void Shader::compileShader()
{
	id = glCreateShader(type);
	const char* shaderSource = source.c_str();
	glShaderSource(id, 1, &shaderSource, nullptr);
	glCompileShader(id);

	// Check for compilation errors
	int compileStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		// Get error length
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* error = new char[length];
		glGetShaderInfoLog(id, length, &length, error);		
		spdlog::error("Failed to compile shader with path '{}':\n{}", filePath, error);
		delete[] error;
		glDeleteShader(id);
	}
}