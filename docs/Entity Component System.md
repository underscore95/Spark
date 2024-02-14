# ECS

Spark uses an ECS (Entity Component System) to handle "game objects". 
Almost everything in your game is an entity, and entities can have components which store information. (Such as ModelComponent storing a reference to the model)
Systems will then handle the logic for the components, for example you could have a ModelSystem which does something like:
```
