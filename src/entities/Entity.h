#pragma once

#include "BaseComponent.h"

namespace Spark::Entity {
	struct Entity {
		std::vector<Spark::Entity::BaseComponent*> components;
		// TODO: bit vector for constant time has-all-components lookup (using a bit mask) (currently linear time)
	};
}