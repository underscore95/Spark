#pragma once

#include <string>

namespace Spark::Logging {
	class Logger;

	enum class LogLevel {
		INFO = 0, WARN = 1, SEVERE = 2
	};

	 Spark::Logging::Logger& getLogger(const std::string& name);
}