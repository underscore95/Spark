#include "SystemManager.h"

namespace SparkInternal::Systems {
	std::vector<std::unique_ptr<Spark::System>> systems;

	void onUpdate(const float dt)
	{
		for (auto& system : systems) {
			system->onUpdate(dt);
		}
	}

	void onRender()
	{
		for (auto& system : systems) {
			system->onRender();
		}
	}

	void onExit()
	{
		systems.clear();
	}
}

void Spark::registerSystem(std::unique_ptr<System> system)
{
	SparkInternal::Systems::systems.push_back(std::move(system));
}