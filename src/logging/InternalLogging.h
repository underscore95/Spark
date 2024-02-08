#pragma once

#include "Logging.h"
#include <chrono>

namespace SparkInternal::Logging {

	struct Log {
		std::chrono::system_clock::time_point time;
		Spark::Logging::LogLevel level;
		std::string loggerName;
		std::string message;
		bool debug;

		Log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level,
			const std::string loggerName, const std::string message, const bool debug) :
			time{ time }, level{ level }, loggerName{ loggerName }, message{ message }, debug{ debug } {}
	};

	// Add a log to the queue
	void log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level,
		const std::string& loggerName, const std::string& message, const bool debug);
}