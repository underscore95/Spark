#pragma once

#include "events/Event.h"

namespace Spark::Events::Types {
	struct WindowCloseEvent : Spark::Events::Event {
		const EventType getType() const {
			return EventType::WindowClose;
		}
	};
}