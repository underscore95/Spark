#pragma once

#include "Logging.h"
#include "pch.h"

namespace Spark::Logging {
	class Logger;
}

namespace SparkInternal::Logging {

	struct Log {
		std::chrono::system_clock::time_point time;
		Spark::Logging::LogLevel level;
		std::string loggerName;
		std::string loggerCreationTime;
		std::string message;
		bool debug;
		bool logToFile;

		Log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level, const std::string& loggerName, const std::string& loggerCreationTime, const std::string& message, bool debug, bool logToFile)
			: time(time), level(level), loggerName(loggerName), loggerCreationTime(loggerCreationTime), message(message), debug(debug), logToFile(logToFile)
		{
		}
	};

	// Add a log to the queue
	void log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level,
		const std::string& loggerName, const std::string& loggerCreationTime, const std::string& message, const bool debug, const bool logToFile);

	// Called when spark exits
	void onExit();
}