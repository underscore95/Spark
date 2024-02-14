#pragma once
#include "System.h"
#include "pch.h"

namespace Spark {
	void registerSystem(std::unique_ptr<System> system);
}

namespace SparkInternal::Systems {
	void onUpdate(const float dt);
	void onRender();
	void onExit();
}