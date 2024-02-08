#include "EventListener.h"
#include "EventHandler.h"

namespace Spark::Events {
	EventListener::EventListener(EventType type) : priority{ EventPriority::NORMAL }
	{
		subscriptions.insert(type);
		registerListener(this);
	}

	EventListener::EventListener(const EventType type, const EventPriority priority) : priority{ priority }
	{
		subscriptions.insert(type);
		registerListener(this);
	}

	EventListener::EventListener(const std::unordered_set<EventType>& types) : subscriptions{ types }, priority{ EventPriority::NORMAL }
	{
		registerListener(this);
	}

	EventListener::EventListener(const std::unordered_set<EventType>& types, const EventPriority priority) : subscriptions{ types }, priority{ priority }
	{
		registerListener(this);
	}

	EventListener::~EventListener()
	{
		unregisterListener(this);
	}

	const EventPriority EventListener::getPriority() const
	{
		return priority;
	}
	const std::unordered_set<EventType>& EventListener::getSubscriptions() const
	{
		return subscriptions;
	}
}