#pragma once

#include "Event.h"
#include "EventContainer.h"

#include "std.h"

namespace Spark::Events {
	class EventListener {
	private:
		short priority;
		std::unordered_set<EventType> subscriptions;

	public:
		// Listen to one event with custom priority
		EventListener(const EventType type, const short priority = 0);
		// Listen to multiple events with one custom priority
		EventListener(const std::unordered_set<EventType>& types, const short priority = 0);

		EventListener(const EventListener&) = delete;
		~EventListener();

		virtual const short getPriority() const final;
		virtual const std::unordered_set<EventType>& getSubscriptions() const final;

		virtual void onEvent(EventContainer& event) const = 0;
	};
}