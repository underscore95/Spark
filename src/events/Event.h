#pragma once

namespace Spark::Events {
	enum class EventType {
		NONE,
		WindowClose
	};

	struct Event {
		virtual const EventType getType() const = 0;
	};
}