#pragma once

#include "pch.h"
#include "BaseComponent.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "ComponentTypeRegistry.h"
#include "View.h"
#include "EntityID.h"
#include "Entity.h"

namespace SparkInternal::Entity {
	inline std::unordered_map<Spark::Entity::EntityID, Spark::Entity::Entity> entities;
	inline Spark::Entity::EntityID lastEntityId = 0;

	inline void removeAllEntities() {
		for (auto& entityPair : entities) {
			for (auto component : entityPair.second.components) {
				if (component != nullptr) {
					delete component;
				}
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
	inline EntityID addEntity() {
		return ++SparkInternal::Entity::lastEntityId;
	}

	// Add a new component to the entity
	template <typename T>
	inline T& addComponent(EntityID entityId) {
		static_assert(std::is_base_of<BaseComponent, T>::value && !std::is_same<BaseComponent, T>::value,
			"T must be a derived class of BaseComponent");

		T* component = new T();
		ComponentID componentId = SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<T>();
		auto& entity = SparkInternal::Entity::entities[entityId];
#ifndef NDEBUG
		if (entity.components.capacity() > componentId && entity.components[componentId] != nullptr) {
			auto& logger = SparkInternal::getLogger();
			logger.severe("Adding duplicate component " + std::to_string(componentId) + " to entity " + std::to_string(entityId) + " (possible memory leaks!)");
		}
#endif

		if (entity.components.capacity() <= componentId) {
			entity.components.resize(componentId + 1);
		}
		entity.components[componentId] = component;
		++(entity.numComponents);
		return *component;
	}

	/*
	* Remove components from an entity.
	* This function will silently fail if no entity with the ID exists.
	* The entity will be removed if there are no remaining components attached.
	* 
	* \param entityID The entity to remove components from
	* 
	* \tparam T Zero or more components to remove from the entity
	*/
	template <typename... T>
	inline void removeComponents(const EntityID& entityId) {
		std::unordered_set<ComponentID> componentIds;
		(componentIds.insert(SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<T>()), ...);

		auto it = SparkInternal::Entity::entities.find(entityId);
		if (it == SparkInternal::Entity::entities.end()) return; // Entity doesn't exist

		auto& comps = it->second.components;
		for (auto compId : componentIds) {
			if (comps[compId] != nullptr) {
				delete comps[compId];
				comps[compId] = nullptr;
				--(it->second.numComponents);
			}
		}

		if (it->second.numComponents == 0) {
			SparkInternal::Entity::entities.erase(entityId);
		}
	}

	// Find all entities with all components, optionally specify a count
	// If a count is specified, and there is more than count matching entities, which entities are returned is undefined.
	// The default if no count is specified will return all matching entities.
	// O(nm) where n is amount of entities and m is amount of components
	template <typename... T>
	inline const Spark::Entity::View getEntities(unsigned int count = UINT_MAX) {
		std::unordered_map<EntityID, Entity> matchingEntities;
		if (count == 0) return matchingEntities;

		// Get all required components
		std::unordered_set<ComponentID> componentIds;
		(componentIds.insert(SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<T>()), ...);

		auto largestComponentId = 0;
		for (const auto componentId : componentIds) {
			if (componentId > largestComponentId) largestComponentId = largestComponentId;
		}

		// Loop over all entities, if entity contains all components, entity matches
		for (auto& entity : SparkInternal::Entity::entities) {
			if (entity.second.numComponents < componentIds.size()) continue;
			if (entity.second.components.size() <= largestComponentId) continue; // Early exit

			bool hasAllComponents = true;
			// Check if entity contains all required components
			for (const auto& componentId : componentIds) {
				if (entity.second.components[componentId] == nullptr) {
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
	inline void removeEntity(EntityID entityId) {
		auto it = SparkInternal::Entity::entities.find(entityId);
		if (it != SparkInternal::Entity::entities.end()) {
			auto& entity = SparkInternal::Entity::entities.at(entityId);
			for (auto& component : entity.components) {
				delete component;
			}

			SparkInternal::Entity::entities.erase(entityId);
		}
	}

	// Get an entity
	inline const Entity& getEntity(EntityID entityId) {
		return SparkInternal::Entity::entities[entityId];
	}
}