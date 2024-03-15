# Input

Each window object can receive user input.
The following examples will assume you have a Window ptr named `window`, see Windows.md if you don't.
To get the user input handler object, use `window->getUserInput();`.

## Example

```
void handleInput() {
	if (window->getUserInput().isKeyDown(Spark::Window::Keyboard::A)) {
		std::cout << "'a' is currently down!\n"; // Printed repeatedly.
	}

	if (window->getUserInput().isKeyPressed(Spark::Window::Keyboard::ESCAPE)) {
		std::cout << "Escape was pressed!\n"; // Printed once and won't be printed again until key is released and re-pressed.
	}

	if (window->getUserInput().isMouseButtonDown(Spark::Window::Mouse::LEFT)) {
		std::cout << "Left mouse button is held down!\n"; // Printed repeatedly.
	}

	if (window->getUserInput().isMouseButtonPressed(Spark::Window::Mouse::MIDDLE)) {
		std::cout << "Middle mouse button was pressed!\n"; // Printed once and won't be printed again until button is released and re-pressed.
	}
}
```