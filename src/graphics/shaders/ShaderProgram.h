#pragma once

#include <vector>
#include "Shader.h"
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

class ShaderProgram {
private:
	unsigned int programId;
	std::unordered_map<std::string, int> cachedUniformLocations;

	const int getUniformLocation(const std::string& variableName);
public:
	// Create a program from the source code of shaders, returning the program id
	ShaderProgram(const std::vector<Shader>& shaders);
	~ShaderProgram();

	const unsigned int getId() const;
	void bind() const;
	void unbind() const;

	void setUniform2f(const std::string name, float v0, float v1);
	void setUniform1i(const std::string name, int i0);
	void setUniformMat4f(const std::string name, const glm::mat4& m0);
};