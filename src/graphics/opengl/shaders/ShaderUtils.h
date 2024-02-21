#pragma once

#include <GL/glew.h>
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "pch.h"

namespace Spark::Graphics::GL {
	inline void compileShader(int type, const std::string& source, const std::string& filePath, unsigned int& id) {
		id = glCreateShader(type);
		const char* shaderSource = source.c_str();
		glShaderSource(id, 1, &shaderSource, nullptr);
		glCompileShader(id);

		auto& logger = SparkInternal::getLogger();

		// Check for compilation errors
		int compileStatus;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			// Get error length
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* error = new char[length];
			glGetShaderInfoLog(id, length, &length, error);
			std::stringstream ss;
			ss << "Failed to compile shader with path '" << filePath << "': \n" << error;
			logger.severe(ss);
			delete[] error;
			glDeleteShader(id);
		}
		else {
			std::stringstream ss;
			ss << "Compiled shader with path '" << filePath << " successfully.";
			logger.info(ss);
		}
	}
}