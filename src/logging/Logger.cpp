#include "Logger.h"
#include <iostream>
#include <magic_enum.hpp>
#include "utils/DateUtils.h"

using namespace Spark::Logging;

void Spark::Logging::Logger::log(const LogLevel level, const bool debug, const std::string& message)
{
#ifdef NDEBUG
	if (debug) return;
#endif

	if (level < this->level) return;

	const std::string currentTime = Spark::Utils::getDateTimeString();
	const std::string logLevelName = std::string(magic_enum::enum_name(level));
	const std::string isDebug = debug ? "[DEBUG] " : "";
	const std::string log = "[" + currentTime + "] [" + logLevelName + "] " + isDebug + "[" + name + "] " + message;

	// Now actually log it
	std::cout << log;

	if (level >= LogLevel::SEVERE) {
		std::cout << std::endl;
	}
	else {
		std::cout << "\n";
	}
}

Spark::Logging::Logger::Logger(const LogLevel level, const std::string& name) : level{ level }, name{ name }
{
}

void Spark::Logging::Logger::info(const std::string& message)
{
	log(LogLevel::INFO, false, message);
}

void Spark::Logging::Logger::warning(const std::string& message)
{
	log(LogLevel::WARN, false, message);
}

void Spark::Logging::Logger::severe(const std::string& message)
{
	log(LogLevel::SEVERE, false, message);
}

void Spark::Logging::Logger::debug(const std::string& message)
{
	log(LogLevel::INFO, true, message);
}

const std::string& Spark::Logging::Logger::getName() const
{
	return name;
}