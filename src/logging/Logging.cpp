#include "Logging.h"
#include "Logger.h"
#include <unordered_map>
#ifndef NDEBUG
#include <iostream>
#endif

using namespace Spark::Logging;

std::unordered_map<std::string, Logger> loggers;

Spark::Logging::Logger& Spark::Logging::getLogger(const std::string& name)
{
#ifndef NDEBUG
	auto it = loggers.find(name);
	if (it == loggers.end()) {
		std::cout << "No logger with name " << name << "exists." << std::endl;
	}
#endif
	return loggers.at(name);
}
