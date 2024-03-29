#pragma once

#include "pch.h"
#include "BaseComponent.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "ComponentTypeRegistry.h"
#include "EntityID.h"
#include "Entity.h"

namespace Spark::Entity {
	class View {
	private:
		const std::unordered_map<EntityID, Entity> entities;

	public:
		// Entity id iterator
		class iterator {
		private:
			using EntityIterator = decltype(entities.begin());
			EntityIterator entityIt;

		public:
			iterator(EntityIterator it);

			// Define iterator operations
			iterator& operator++();
			bool operator!=(const iterator& other) const;

			// Dereference operator
			EntityID operator*() const;
		};

		View() = delete;
		View(const View&) = delete;
		View(const std::unordered_map<EntityID, Entity>& entities)
			: entities{ entities } {};

		iterator begin() const;
		iterator end() const;

		size_t count() const;

		// Get all components of a specific type on this entity
		template<typename... T>
		inline std::tuple<T&...> get(EntityID entityId) const {
			auto it = entities.find(entityId);
#ifndef NDEBUG
			if (it == entities.end()) {
				auto& logger = SparkInternal::getLogger();
				logger.severe("Tried to get components of entity " + std::to_string(entityId) + " that isn't in view");
			}
#endif
			// Get this entity
			const Entity& thisEntity = it->second;

			// Get all the requested components
			return std::tie(dynamic_cast<T&>(*thisEntity.components.at(SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<T>()))...);
		}

	};
}
