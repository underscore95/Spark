#pragma once

#include "pch.h"
#include "BaseComponent.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "ComponentTypeRegistry.h"
#include "View.h"

namespace SparkInternal::Entity {
	inline std::unordered_map<unsigned int, std::unordered_map<size_t, Spark::Entity::BaseComponent*>> entities;
	inline unsigned int lastEntityId = 0;

	inline void removeAllEntities() {
		for (auto& entityPair : entities) {
			for (auto& componentPair : entityPair.second) {
				delete componentPair.second;
			}
		}

		entities.clear();
	}

	inline void onExit() {
		removeAllEntities();

		auto* typeRegistry = &(SparkInternal::Entity::ComponentTypeRegistry::getInstance());
		delete typeRegistry;
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
		size_t componentId = SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<T>();
		auto& entity = SparkInternal::Entity::entities[entityId];
#ifndef NDEBUG
		if (entity.find(componentId) != entity.end()) {
			auto& logger = SparkInternal::getLogger();
			logger.warning("Adding duplicate component " + std::to_string(componentId) + " to entity " + std::to_string(entityId));
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
	inline const Spark::Entity::View getEntities(unsigned int count = UINT_MAX) {
		std::unordered_map<unsigned int, std::unordered_map<size_t, Spark::Entity::BaseComponent*>> matchingEntities;
		if (count == 0) return matchingEntities;

		// Get all required components
		std::unordered_set<size_t> componentIds;
		(componentIds.insert(SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<T>()), ...);

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
				matchingEntities.insert(entity);
				if (matchingEntities.size() >= count) break;
			}
		}
		return Spark::Entity::View(matchingEntities);
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
	inline const std::unordered_map<size_t, Spark::Entity::BaseComponent*>& getEntity(unsigned int entityId) {
		return SparkInternal::Entity::entities[entityId];
	}
}