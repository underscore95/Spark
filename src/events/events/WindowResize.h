#pragma once

#include "events/Event.h"

namespace Spark::Events::Types {
	struct WindowResize : Spark::Events::Event {
		const EventType getType() const {
			return EventType::WindowResize;
		}
	};
}