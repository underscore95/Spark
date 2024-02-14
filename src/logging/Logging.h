#pragma once

#include "pch.h"

namespace Spark::Logging {
	class Logger;

	enum class LogLevel {
		INFO = 0, WARN = 1, SEVERE = 2
	};

	Logger& getLogger(const std::string& name);
	void registerLogger(std::unique_ptr<Spark::Logging::Logger> logger);
}

namespace Spark {
	inline Spark::Logging::Logger& getLogger(const std::string& name) { return Spark::Logging::getLogger(name); }
}

namespace SparkInternal {
	inline Spark::Logging::Logger& getLogger() { return Spark::Logging::getLogger("spark"); }
}