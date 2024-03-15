#include "Input.h"
#include "window/abstract/Window.h"

namespace Spark::Window {
	void Input::setMouseButtonPressed(MouseButton button)
	{
		mouseButtonsPressed.insert(button);
	}

	void Input::handleInputSetup()
	{
		mouseButtonsPressedLastFrame = mouseButtonsPressed;
		mouseButtonsPressed.clear();
	}

	[[nodiscard]] constexpr const glm::vec2 Input::getClampedMousePos() const {
		auto pos = mousePosition;
		pos.x = std::clamp((int)pos.x, 0, (int)window->getDimensions().x);
		pos.y = std::clamp((int)pos.y, 0, (int)window->getDimensions().y);
		return pos;
	}
}