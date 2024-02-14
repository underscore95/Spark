# ECS

Spark uses an ECS (Entity Component System) to handle "game objects". 
Almost everything in your game is an entity, and entities can have components which store information. (Such as ModelComponent storing a reference to the model)

# Spawning an entity
An entity is an id and a collection of components. You can get an unused entity id with `auto entity = Spark::Entity::addEntity();`
Note that without any components / systems, this does nothing.

# Adding components
You can create a component by creating a class which inherits from `Spark::Entity::BaseComponent`.
You can add a component to your entity using `auto& comp = Spark::Entity::addComponent<YourComponent>(entity);`. Note that your component must have a default constructor. (planned to change)

# Getting components on an entity
`const auto& comps = Spark::Entity::getEntity(entity);`
This will return a reference to a map of internal component ids and component pointers.
You should not be storing these pointers though.

# Removing entities
`Spark::Entity::removeEntity(entity);` will remove the entity and free the components' memory.

# Views
A view is a collection of entities which have a specific set of components.
`auto& view = Spark::Entity::getEntities<TestComponent>(); // Contains all entities with TestComponent`
`auto& view = Spark::Entity::getEntities<TestComponent, Test2Component>(); // Contains all entities with TestComponent and Test2Component`

You can iterate views:
`for (auto entity : view) {} // entity is an entity id (unsigned int)`

You can get components on a specific entity in a view:
`auto [ testComponent ] = view.get<TestComponent>(entity); // Would be used when iterating over a view`

You can specify parameters in any order, so even if you have a `View` of `<TestComponent, Test2Component>`, you can `get` `<Test2Component, TestComponent>`, or even just `Test2Component`.
Note that you should never store a view.

# Systems (unimplemented)
Systems will then handle the logic for the components, for example you could have a ModelSystem which does something like:
```
auto& view = Spark::Entity::getEntities<ModelComponent, TransformComponent>();
for (auto entity : view) {
	auto [ transformComp, modelComp ] = view.get<TransformComponent, ModelComponent>(entity);
	ModelManager::renderModel(modelComp.modelId, transformComp.position);
}
```