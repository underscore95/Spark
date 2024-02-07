#include "SparkEngine.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

bool initialised = false;

void Spark::init()
{
	if (isInitialised()) return;

	initialised = true;
	Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "spark"));

	auto logger = Spark::Logging::getLogger("spark");
	logger.info("Initialised Spark Engine");
}

bool Spark::isInitialised()
{
	return initialised;
}
