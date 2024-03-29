#pragma once

#include "Logging.h"

#include "pch.h"
#include "utils/DateUtils.h"

namespace Spark::Logging {
	class Logger {
	public:
		LogLevel level;
	private:
		std::string name;
		bool fileLoggingEnabled;

		void log(const LogLevel level, const bool debug, const std::string& message) const;

	public:
		const std::string creationTime = Spark::Utils::getDateTimeString(std::chrono::system_clock::now(), true);

		Logger(const LogLevel level, const std::string& name, const bool fileLoggingEnabled = true);

		void info(const std::string& message) const;
		void warning(const std::string& message) const;
		void severe(const std::string& message) const;
		void debug(const std::string& message) const;

		void info(std::stringstream& ss) const;
		void warning(std::stringstream& ss) const;
		void debug(std::stringstream& ss) const;
		void severe(std::stringstream& ss) const;

		const std::string getName() const;
	};
}