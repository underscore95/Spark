#pragma once

#include "pch.h"
#include "BaseComponent.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

namespace SparkInternal::Entity {
	inline std::unordered_map<unsigned int, std::unordered_map<std::string, Spark::Entity::BaseComponent*>> entities;
	inline unsigned int lastEntityId = 0;

	inline void onExit() {
		for (auto& entityPair : entities) {
			for (auto& componentPair : entityPair.second) {
				delete componentPair.second;
			}
		}
		entities.clear();
	}
}

namespace Spark::Entity {
	// Returns a new entity id, which you can use to add components to.
	inline unsigned int addEntity() {
		// Entities don't really exist, all we use is an id, so we don't need to do anything other than return a new unique id
		return ++SparkInternal::Entity::lastEntityId;
	}

	// Add a new component to the entity
	template <typename T>
	inline T& addComponent(unsigned int entityId) {
		static_assert(std::is_base_of<BaseComponent, T>::value && !std::is_same<BaseComponent, T>::value,
			"T must be a derived class of BaseComponent");

		T* component = new T();
		std::string componentId = typeid(T).name();
		auto& entity = SparkInternal::Entity::entities[entityId];
#ifndef NDEBUG
		if (entity.find(componentId) != entity.end()) {
			auto& logger = Spark::Logging::getLogger("spark");
			logger.warning("Adding duplicate component " + componentId + " to entity " + std::to_string(entityId));
		}
#endif

		entity.insert(std::pair(componentId, component));
		return *component;
	}

	// Find all entities with all components, optionally specify a count
	// If a count is specified, and there is more than count matching entities, which entities are returned is undefined.
	// The default if no count is specified will return all matching entities.
	// O(nm) where n is amount of entities and m is amount of components
	template <typename... T>
	inline const std::vector<unsigned int>& getEntities(unsigned int count = UINT_MAX) {
		std::vector<unsigned int> matchingEntities;
		if (count == 0) return matchingEntities;

		// Get all required components
		std::unordered_set<std::string> componentIds;
		//(componentIds.insert(SparkInternal::ComponentTypeRegistry::getInstance().getTypeId<T>()), ...);

		// Loop over all entities, if entity contains all components, entity matches
		for (const auto& entity : SparkInternal::Entity::entities) {
			bool hasAllComponents = true;
			// Check if entity contains all required components
			for (const auto& componentId : componentIds) {
				if (entity.second.find(componentId) == entity.second.end()) {
					hasAllComponents = false;
					break;
				}
			}


			if (hasAllComponents) {
				matchingEntities.push_back(entity.first);
				if (matchingEntities.size() >= count) break;
			}
		}
		return matchingEntities;
	}

	// Remove an entity, deleting all its components
	inline void removeEntity(unsigned int entityId) {
		auto it = SparkInternal::Entity::entities.find(entityId);
		if (it != SparkInternal::Entity::entities.end()) {
			auto& entity = SparkInternal::Entity::entities.at(entityId);
			for (auto& componentPair : entity) {
				delete componentPair.second;
			}

			SparkInternal::Entity::entities.erase(entityId);
		}
	}

	// Get all components on an entity
	inline std::unordered_map<std::string, Spark::Entity::BaseComponent*>& getEntity(unsigned int entityId) {
		return SparkInternal::Entity::entities[entityId];
	}
}