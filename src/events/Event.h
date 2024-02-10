#pragma once

namespace Spark::Events {
	enum class EventType {
		NONE,
		WindowResize
	};

	struct Event {
		virtual const EventType getType() const = 0;
	};
}