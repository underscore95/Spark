#pragma once

#include "pch.h"
#include "BaseComponent.h"
#include "EntityID.h"

namespace SparkInternal::Entity {
	// Define a type registry to map component types to unique identifiers
	class ComponentTypeRegistry {
	private:
		static inline ComponentTypeRegistry* instance;
		std::unordered_map<std::type_index, Spark::Entity::ComponentID> typeIds;
	public:
		static ComponentTypeRegistry& getInstance() {
			if (!instance) instance = new ComponentTypeRegistry();
			return *instance;
		}

		template<typename T>
		Spark::Entity::ComponentID getTypeId() {
			static_assert(std::is_base_of<Spark::Entity::BaseComponent, T>::value && !std::is_same<Spark::Entity::BaseComponent, T>::value,
				"T must be a derived class of BaseComponent");

			auto typeIdIt = typeIds.find(typeid(T));
			if (typeIdIt == typeIds.end()) {
				// Generate a new type id for the component type
				Spark::Entity::ComponentID newTypeId = typeIds.size();
				typeIds[typeid(T)] = newTypeId;
				return newTypeId;
			}
			return typeIdIt->second;
		}
	};
}