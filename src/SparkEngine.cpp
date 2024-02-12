#include "SparkEngine.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "logging/InternalLogging.h"

namespace SparkInternal {
	Spark::Application* app;

	static void handleExit()
	{
		auto& logger = Spark::Logging::getLogger("spark");
		logger.info("Exiting Spark Engine...");

		SparkInternal::Logging::onExit();

		delete app;
	}

	static void mainLoop() {
		while (app->isRunning()) {
			app->update();
			app->render();
		}

		handleExit();
	}

	void init(std::function<Spark::Application* ()> appInitialiser)
	{
		Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "spark"));

		auto& logger = Spark::Logging::getLogger("spark");
		std::stringstream ss;
		ss << "Initialised Spark Engine " << SPARK_VERSION;
		logger.info(ss);

		app = appInitialiser(); // This should be the last thing in the init function
		mainLoop();
	}
}