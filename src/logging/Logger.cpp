#include "Logger.h"
#include "InternalLogging.h"
#include <iostream>

using namespace Spark::Logging;

void Spark::Logging::Logger::log(const LogLevel level, const bool debug, const std::string& message)
{
#ifdef NDEBUG
	if (debug) return;
#endif

	if (level < this->level) return;
	SparkInternal::Logging::log(std::chrono::system_clock::now(), level, name, message, debug);
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