#include "EventHandler.h"
#include "EventListener.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

#include <magic_enum.hpp>
#include "pch.h"

namespace Spark::Events {

	// type : [priority : {listener}]
	// For every type that a listener subscribes to, a <priority, listener*> pair will be stored
	// This allows for o(T) (where T = number of subscribed event types) registration and unregistration
	std::unordered_map<EventType, std::map<short, std::vector<const EventListener*>>> listeners;

	void registerListener(const EventListener* listener)
	{
		auto& logger = SparkInternal::getLogger();
		logger.debug("Registered listener");


		const short priority = listener->getPriority();
		const std::unordered_set<EventType> types = listener->getSubscriptions();

		for (const EventType type : types) {
			auto& typeListeners = listeners[type][priority];
#ifndef NDEBUG
			// Duplicate listener registration warning
			auto it = std::find(typeListeners.begin(), typeListeners.end(), listener);
			if (it != typeListeners.end()) {
				auto& logger = SparkInternal::getLogger();
				logger.warning("Duplicate registration for event listener " + std::to_string((unsigned long long)listener) + " (type=" + std::string(magic_enum::enum_name(type)) + ")");
			}

			// NONE event type
			if (type == EventType::NONE) {
				auto& logger = SparkInternal::getLogger();
				logger.warning("Registered event listener with event type NONE: " + std::to_string((unsigned long long)listener));
			}
#endif
			typeListeners.push_back(listener);
		}
	}

	void unregisterListener(const EventListener* listener)
	{
		auto& logger = SparkInternal::getLogger();
		logger.debug("Unregistered listener");

		const short priority = listener->getPriority();
		const std::unordered_set<EventType> types = listener->getSubscriptions();

		for (const EventType type : types) {
			auto& typeListeners = listeners[type][priority];
			auto it = std::find(typeListeners.begin(), typeListeners.end(), listener);
			if (it != typeListeners.end()) {
				typeListeners.erase(it);
			}
		}
	}

	void callEvent(const Event& event)
	{
		const auto type = event.getType();
		if (type == EventType::NONE) {
			auto& logger = SparkInternal::getLogger();
			logger.warning("Called event with NONE type");
			return;
		}

		EventContainer container(event);

		std::map<short, std::vector<const EventListener*>>& typeListeners = listeners[type];
		for (std::pair<short, std::vector<const EventListener*>> priorityPair : typeListeners) { // priority, vector<listener>
			std::vector<const EventListener*>& relevantListeners = priorityPair.second;
			for (const EventListener* listener : relevantListeners) {
				listener->onEvent(container);
				if (container.handled) return;
			}
		}
	}
}