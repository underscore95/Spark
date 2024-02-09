#pragma once

#include "Event.h"

class EventListener;

namespace Spark::Events {
	// You probably don't need these, as EventListener will register & unregister itself during its lifetime
	void registerListener(const EventListener* listener);
	void unregisterListener(const EventListener* listener);

	// Send the event to all the subscribed event listeners
	void callEvent(const Event& event);
}