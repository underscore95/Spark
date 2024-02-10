#include "WindowFactory.h"

#ifdef _WIN32
#include "window/glfw/GLFWWindow.h"
#endif

std::unique_ptr<Spark::Window::Window> Spark::Window::create(const std::string& title, const glm::uvec2& dimensions) {
	// GLFW WINDOWS
#ifdef _WIN32
	return std::make_unique<Spark::Window::GLFWWindow>(title, dimensions);
#else
	throw std::runtime_error("Platform not supported for window creation.");
#endif
}