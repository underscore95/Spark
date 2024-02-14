#include "SparkEngine.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "logging/InternalLogging.h"
#include "entities/EntityManager.h"

namespace SparkInternal {
	Spark::Application* app;
	unsigned int fps = 0;

	static void handleExit()
	{
		auto& logger = Spark::Logging::getLogger("spark");
		logger.info("Exiting Spark Engine...");

		SparkInternal::Logging::onExit();
		SparkInternal::Entity::onExit();

		delete app;
	}

	static void mainLoop() {
		float deltaTime = 1.0 / 120.0;

		auto lastFPSCalculation = std::chrono::system_clock::now();
		unsigned int framesThisSecond = 0;
		while (app->isRunning()) {
			auto startFrame = std::chrono::system_clock::now();

			// MAIN GAME LOGIC -------
			app->update(deltaTime);
			app->render();
			// END MAIN GAME LOGIC -----

			auto endFrame = std::chrono::system_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(endFrame - startFrame).count();

			++framesThisSecond;
			if (endFrame - lastFPSCalculation >= std::chrono::seconds(1)) {
				fps = framesThisSecond;
				framesThisSecond = 0;
				lastFPSCalculation = endFrame;
			}
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

const unsigned int Spark::getFPS()
{
	return SparkInternal::fps;
}
