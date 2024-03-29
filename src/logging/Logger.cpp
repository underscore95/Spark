#include "Logger.h"
#include "InternalLogging.h"

using namespace Spark::Logging;

void Spark::Logging::Logger::log(const LogLevel level, const bool debug, const std::string& message) const
{
#ifdef NDEBUG
	if (debug) return;
#endif

	if (level < this->level) return;
	SparkInternal::Logging::log(std::chrono::system_clock::now(), level, name, creationTime, message, debug, fileLoggingEnabled);
}

Spark::Logging::Logger::Logger(const LogLevel level, const std::string& name, const bool fileLoggingEnabled) : level{ level }, name{ name }, fileLoggingEnabled{ fileLoggingEnabled }
{
}

void Spark::Logging::Logger::info(const std::string& message) const
{
	log(LogLevel::INFO, false, message);
}

void Spark::Logging::Logger::warning(const std::string& message) const
{
	log(LogLevel::WARN, false, message);
}

void Spark::Logging::Logger::severe(const std::string& message) const
{
	log(LogLevel::SEVERE, false, message);
}

void Spark::Logging::Logger::debug(const std::string& message) const
{
	log(LogLevel::INFO, true, message);
}

void Spark::Logging::Logger::info(std::stringstream& ss) const
{
	info(ss.str());
}

void Spark::Logging::Logger::warning(std::stringstream& ss) const
{
	warning(ss.str());
}

void Spark::Logging::Logger::debug(std::stringstream& ss) const
{
	debug(ss.str());
}

void Spark::Logging::Logger::severe(std::stringstream& ss) const
{
	severe(ss.str());
}

const std::string Spark::Logging::Logger::getName() const
{
	return name;
}