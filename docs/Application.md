# Application

The `Application` class is a fundamental component of the Spark game engine. It serves as the base for all user-defined applications within the engine, providing essential functionalities for initialization, execution, and termination of the application.

### Important Methods:
- The `stop()` method is used to halt the execution of the application. It serves as the exit point of the application loop.
- The `update()` method is responsible for updating the application's logic, such as input handling, physics simulation, and game state management.
- The `render()` method is responsible for rendering the application's content, including graphics, user interfaces, and visual effects.

## Inheritance
- The `Application` class is designed to be inherited by user-defined application classes. Derived classes should implement the `update()` and `render()` methods to define the behavior of the application.

## Example
```cpp
class MyApplication : public Spark::Application {
public:
    void update() override {
        // Implement application logic update here
    }

    void render() override {
        // Implement application rendering here
    }
};

int main() {
    Spark::init<MyApplication>();
    return 0;
}
```