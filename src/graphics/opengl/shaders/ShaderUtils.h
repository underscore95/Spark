#pragma once

#include <GL/glew.h>
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "pch.h"

namespace Spark::Graphics::GL {
	void compileShader(int type, const std::string& source, const std::string& filePath, unsigned int& id);
}