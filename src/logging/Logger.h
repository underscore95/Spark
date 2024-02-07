#pragma once

#include <string>
#include "Logging.h"

namespace Spark::Logging {
	class Logger {
	public:
		LogLevel level;
	private:
		std::string name;

		void log(const LogLevel level, const bool debug, const std::string& message);

	public:
		Logger(const LogLevel level, const std::string& name);

		void info(const std::string& message);
		void warning(const std::string& message);
		void severe(const std::string& message);
		void debug(const std::string& message);

		const std::string& getName() const;
	};
}