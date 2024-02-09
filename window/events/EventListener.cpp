#include "EventListener.h"
#include "EventHandler.h"

namespace Spark::Events {
	EventListener::EventListener(EventType type) : priority{ 0 }
	{
		subscriptions.insert(type);
		registerListener(this);
	}

	EventListener::EventListener(const EventType type, const short priority) : priority{ priority }
	{
		subscriptions.insert(type);
		registerListener(this);
	}

	EventListener::EventListener(const std::unordered_set<EventType>& types) : subscriptions{ types }, priority{ 0 }
	{
		registerListener(this);
	}

	EventListener::EventListener(const std::unordered_set<EventType>& types, const short priority) : subscriptions{ types }, priority{ priority }
	{
		registerListener(this);
	}

	EventListener::~EventListener()
	{
		unregisterListener(this);
	}

	const short EventListener::getPriority() const
	{
		return priority;
	}

	const std::unordered_set<EventType>& EventListener::getSubscriptions() const
	{
		return subscriptions;
	}
}