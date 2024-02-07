#include "Logging.h"
#include "Logger.h"
#include <unordered_map>
#ifndef NDEBUG
#include <iostream>
#endif

using namespace Spark::Logging;

std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;

std::shared_ptr<Logger> Spark::Logging::getLogger(const std::string& name)
{
#ifndef NDEBUG
	auto it = loggers.find(name);
	if (it == loggers.end()) {
		std::cout << "No logger with name " << name << " exists." << std::endl;
	}
#endif
	return loggers.at(name);
}

void Spark::Logging::registerLogger(std::unique_ptr<Spark::Logging::Logger> logger)
{
#ifndef NDEBUG
	// Check if logger already exists
	const std::string loggerName = logger->getName();

	auto it = loggers.find(loggerName);
	if (it != loggers.end()) {
		std::cout << "Logger with name " << loggerName << " was registered multiple times." << std::endl;
	}
#endif

	// Register the logger
	loggers.insert(std::pair<std::string, std::shared_ptr<Logger>>(logger->getName(), std::move(logger)));

#ifndef NDEBUG
	// Ensures the logger was successfully registered
	getLogger(loggerName)->debug("Logger Registered");
#endif
}

// Register sparks logger
#ifndef SPARK_INTERNAL_LOGGER
#define SPARK_INTERNAL_LOGGER
namespace SparkInternal::Logging {
	bool registerSparkLogger() {
		Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "spark"));
		return true;
	}

	bool didRegisterSparkLogger = registerSparkLogger();
}
#endif