#pragma once

#include "Logging.h"
#include "Logger.h"
#include <memory>

namespace SparkInternal::Logging {
	bool registerSparkLogger() {
		Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "spark"));
		return true;
	}

	bool didRegisterSparkLogger = registerSparkLogger();
}