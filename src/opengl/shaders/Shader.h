#pragma once

#include <fstream>
#include <string>
#include <vector>

class Shader {
public:
	Shader(const std::string& filePath, int shaderType);

	const unsigned int getShaderId() const;

private:
	// Read a shader file, assigning the source code
	void readShaderFile();

	// Compile the shader, assigning the shader id
	void compileShader();

	std::string source{ "" };
	int type;
	std::string filePath;
	unsigned int id{ 0 };
};