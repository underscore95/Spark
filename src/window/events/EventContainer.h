#pragma once

#include "Event.h"

namespace Spark::Events {
	struct EventContainer {
	public:
		const Event& event;
		bool handled = false;

		EventContainer(const Event& event) : event{ event } {};
	};
}