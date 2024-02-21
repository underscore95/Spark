#pragma once

#include "BaseComponent.h"

namespace Spark::Entity {
	struct Entity {
		std::vector<Spark::Entity::BaseComponent*> components;
	};
}