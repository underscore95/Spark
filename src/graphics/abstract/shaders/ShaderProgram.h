#pragma once

#include "pch.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace Spark::Graphics {
	class ShaderProgram {
	protected:
		unsigned int rendererId;
		std::unordered_map<std::string, int> cachedUniformLocations;

		virtual	const int getUniformLocation(const std::string& variableName) = 0;
	public:
		const unsigned int getRendererId() const;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setUniform2f(const std::string name, float v0, float v1) = 0;
		virtual void setUniform1i(const std::string name, int i0) = 0;
		virtual void setUniformMat4f(const std::string name, const glm::mat4& m0) = 0;
	};
}