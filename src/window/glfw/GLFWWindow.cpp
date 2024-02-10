#include "GLFWWindow.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

void errorCallback(int error, const char* description)
{
	auto& logger = Spark::Logging::getLogger("spark");
	std::stringstream ss;
	ss << "glfw error occurred. (Error Code: " << error << ")\n" << description;
	logger.severe(ss);
}

bool Spark::Window::GLFWWindow::createWindow()
{
	auto& logger = Spark::Logging::getLogger("spark");
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		logger.severe("Failed to initialise GLFW");
		return false;
	}

	window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), NULL, NULL);
	if (!window) {
		logger.severe("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

Spark::Window::GLFWWindow::GLFWWindow(const std::string& title, const glm::uvec2& dimensions) : Window(title)
{
	this->successfullyInitialised = createWindow();
}

Spark::Window::GLFWWindow::~GLFWWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Spark::Window::GLFWWindow::update()
{
	if (isWindowClosed()) return;

	if (glfwWindowShouldClose(window)) {
		windowClosed = true;
		return;
	}

	glfwSwapBuffers(window);

	glfwPollEvents();
}

void Spark::Window::GLFWWindow::setTitle(const std::string& title)
{
	if (isWindowOpen()) {
		this->title = title;
		glfwSetWindowTitle(window, this->title.c_str());
	}
}

void Spark::Window::GLFWWindow::setDimensions(const glm::uvec2& dimensions)
{
	if (isWindowOpen()) {
		this->dimensions = dimensions;
		glfwSetWindowSize(window, dimensions.x, dimensions.y);
	}
}
