#pragma once

#include "pch.h"

namespace SparkInternal::Entity {
    // Define a type registry to map component types to unique identifiers
    class ComponentTypeRegistry {
    private:
        static ComponentTypeRegistry* instance;
        std::unordered_map<std::type_index, size_t> typeIds;
    public:
        static ComponentTypeRegistry& getInstance() {
            if (!instance) instance = new ComponentTypeRegistry();
            return *instance;
        }

        template<typename T>
        size_t getTypeId() {
            auto typeIdIt = typeIds.find(typeid(T));
            if (typeIdIt == typeIds.end()) {
                // Generate a new type id for the component type
                size_t newTypeId = typeIds.size();
                typeIds[typeid(T)] = newTypeId;
                return newTypeId;
            }
            return typeIdIt->second;
        }
    };
}