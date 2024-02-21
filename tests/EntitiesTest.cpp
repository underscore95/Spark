#include <gtest/gtest.h>

#include "Spark.h"
#include "pch.h"

class TestComponent : public Spark::Entity::BaseComponent {
public: 
    unsigned short a;
};

TEST(Entities, addEntityGivesUniqueId) {
    ASSERT_NE(Spark::Entity::addEntity(), Spark::Entity::addEntity());

    SparkInternal::Entity::removeAllEntities();
}

TEST(Entities, addComponentAndGetEntity) {
    auto entity = Spark::Entity::addEntity();
    auto& test = Spark::Entity::addComponent<TestComponent>(entity);
    test.a = 2;

    const auto testComponentId = SparkInternal::Entity::ComponentTypeRegistry::getInstance().getTypeId<TestComponent>();

    const auto& comps = Spark::Entity::getEntity(entity).components;
    ASSERT_EQ(comps.size(), 1); // Ensure only one component added
    auto baseComponent = comps[testComponentId];
    ASSERT_TRUE(baseComponent != nullptr); // Ensure TestComponent is added
    TestComponent* testComponent = dynamic_cast<TestComponent*>(baseComponent);
    ASSERT_TRUE(testComponent != nullptr); // Ensure correct component type
    ASSERT_EQ(testComponent->a, 2); // Ensure component data is set correctly

    SparkInternal::Entity::removeAllEntities();
}

TEST(EntitiesTest, numComponents) {
    auto id = Spark::Entity::addEntity();
    auto& testComponent = Spark::Entity::addComponent<TestComponent>(id);
    const auto& entity = Spark::Entity::getEntity(id);

    ASSERT_EQ(entity.numComponents, 1);
    SparkInternal::Entity::removeAllEntities();
}

TEST(EntitiesTest, removeComponents) {
    auto id = Spark::Entity::addEntity();
    auto& testComponent = Spark::Entity::addComponent<TestComponent>(id);
    const auto& entity = Spark::Entity::getEntity(id);

    ASSERT_EQ(entity.numComponents, 1);
    Spark::Entity::removeComponents<TestComponent>(id);

    // Removing last component should delete the entity
    ASSERT_EQ(0, Spark::Entity::getEntities<TestComponent>().count());
}

TEST(Entities, addComponentAndView) {
    SparkInternal::Entity::removeAllEntities();

    auto entId = Spark::Entity::addEntity();
    auto& test = Spark::Entity::addComponent<TestComponent>(entId);
    test.a = 2;

    auto& view = Spark::Entity::getEntities<TestComponent>();
    for (auto entity : view) {
        auto [ testComponent ] = view.get<TestComponent>(entity);
        ASSERT_EQ(testComponent.a, 2); // Ensure component data is set correctly
        // Ensure it is updated
        testComponent.a = 3;
    }

    ASSERT_EQ(test.a, 3);

    SparkInternal::Entity::removeAllEntities();
}

TEST(Entities, getEntitiesByComponentType) {
    auto entity1 = Spark::Entity::addEntity();
    auto& test1 = Spark::Entity::addComponent<TestComponent>(entity1);
    test1.a = 5;

    auto entity2 = Spark::Entity::addEntity();
    auto& test2 = Spark::Entity::addComponent<TestComponent>(entity2);
    test2.a = 10;

    auto& entitiesWithTest = Spark::Entity::getEntities<TestComponent>();
    ASSERT_EQ(entitiesWithTest.count(), 2); // Ensure both entities are found

    for (auto entityId : entitiesWithTest) {
        auto [testComp] = entitiesWithTest.get<TestComponent>(entityId);
        if (entityId == entity1) {
            ASSERT_EQ(testComp.a, 5); // Ensure correct data for entity 1
        }
        else if (entityId == entity2) {
            ASSERT_EQ(testComp.a, 10); // Ensure correct data for entity 2
        }
    }

    SparkInternal::Entity::removeAllEntities();
}

TEST(Entities, removeEntity) {
    auto entity = Spark::Entity::addEntity();
    Spark::Entity::addComponent<TestComponent>(entity);
    Spark::Entity::removeEntity(entity);
    const auto& comps = Spark::Entity::getEntity(entity).components;
    ASSERT_TRUE(comps.empty()); // Ensure entity is removed

    SparkInternal::Entity::removeAllEntities();
}

TEST(Entities, removeAllEntities) {
    for (int i = 0; i < 5; ++i) {
        auto entity = Spark::Entity::addEntity();
        Spark::Entity::addComponent<TestComponent>(entity);
    }

    SparkInternal::Entity::removeAllEntities();
    ASSERT_TRUE(SparkInternal::Entity::entities.empty());
}