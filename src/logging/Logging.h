#pragma once

#include <string>
#include <memory>

namespace Spark::Logging {
	class Logger;

	enum class LogLevel {
		INFO = 0, WARN = 1, SEVERE = 2
	};

	Logger& getLogger(const std::string& name);
	void registerLogger(std::unique_ptr<Spark::Logging::Logger> logger);
}