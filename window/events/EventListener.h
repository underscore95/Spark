#pragma once

#include "Event.h"
#include "EventPriority.h"
#include <unordered_set>
#include "EventContainer.h"

namespace Spark::Events {
	class EventListener {
	private:
		EventPriority priority;
		std::unordered_set<EventType> subscriptions;

	public:
		// Listen to one event with normal priority
		EventListener(const EventType type);
		// Listen to one event with custom priority
		EventListener(const EventType type, const EventPriority priority);
		// Listen to multiple events with normal priority
		EventListener(const std::unordered_set<EventType>& types);
		// Listen to multiple events with one custom priority
		EventListener(const std::unordered_set<EventType>& types, const EventPriority priority);

		EventListener(const EventListener&) = delete;
		~EventListener();

		virtual const EventPriority getPriority() const final;
		virtual const std::unordered_set<EventType>& getSubscriptions() const final;

		virtual void onEvent(EventContainer& event) const = 0;
	};
}