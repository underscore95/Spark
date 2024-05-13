#include "SparkEngine.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "logging/InternalLogging.h"
#include "entities/EntityManager.h"
#include "systems/SystemManager.h"
#include "graphics/api/GraphicsFactory.h"
#include "graphics/api/camera/CameraController.h"
#include "audio/Audio.h"

namespace SparkInternal {
	Spark::Application* app;
	unsigned int fps = 0;

	static void handleExit()
	{
		auto& logger = SparkInternal::getLogger();
		logger.info("Exiting Spark Engine...");

		SparkInternal::Systems::onExit();
		SparkInternal::Entity::onExit();
		SparkInternal::Logging::onExit();

		delete app;

		SparkInternal::Audio::onExit();
	}

	static void mainLoop() {
		float deltaTime = 1.0 / 120.0;

		auto lastFPSCalculation = std::chrono::system_clock::now();
		unsigned int framesThisSecond = 0;
		while (app->isRunning()) {
			auto startFrame = std::chrono::system_clock::now();

			// ------- MAIN GAME LOGIC -------
			// ------- INPUT -------
			SparkInternal::Graphics::CameraControllerManager::singleton().handleInput(deltaTime);
			// ------- UPDATE -------
			app->update(deltaTime);
			SparkInternal::Systems::onUpdate(deltaTime);

			// ------- RENDER -------
			SparkInternal::Graphics::CameraControllerManager::singleton().update(deltaTime);
			app->render();
			SparkInternal::Systems::onRender();
			// ------- END MAIN GAME LOGIC -----

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
		// Logging should be first thing done
		Spark::Logging::registerLogger(std::make_unique<Spark::Logging::Logger>(Spark::Logging::LogLevel::INFO, "spark"));

		auto& logger = SparkInternal::getLogger();
		std::stringstream ss;
		ss << "Initialised Spark Engine " << SPARK_VERSION;
		logger.info(ss);

		// Audio
		SparkInternal::Audio::init();

		// Start the game
		app = appInitialiser(); // This should be the last thing in the init function
		mainLoop();
	}
}

const unsigned int Spark::getFPS()
{
	return SparkInternal::fps;
}
