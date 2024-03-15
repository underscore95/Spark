#include "Window.h"

Spark::Window::Window::Window(const std::string& title, const glm::uvec2& dimensions) : title{ title }, dimensions{ dimensions }, input{ this }
{
}

const bool Spark::Window::Window::isSuccessfullyInitialised() const
{
	return successfullyInitialised;
}

const std::string& Spark::Window::Window::getTitle() const
{
	return title;
}

const glm::uvec2 Spark::Window::Window::getDimensions() const
{
	return dimensions;
}

const bool Spark::Window::Window::isWindowClosed() const
{
	return windowClosed;
}

const bool Spark::Window::Window::isWindowOpen() const
{
	return !isWindowClosed() && isSuccessfullyInitialised();
}

void Spark::Window::Window::setSwapInterval(int interval)
{
}

Spark::Window::Input& Spark::Window::Window::getUserInput()
{
	return input;
}
