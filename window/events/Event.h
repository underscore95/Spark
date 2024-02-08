#pragma once

namespace Spark::Events {
	enum class EventType {
		NONE,
		WindowClose
	};

	struct Event {
		EventType type = EventType::NONE;
	};
}