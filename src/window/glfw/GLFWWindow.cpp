#include "GLFWWindow.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include "events/EventHandler.h"
#include "events/Events.h"

void errorCallback(int error, const char* description) {
	auto& logger = SparkInternal::getLogger();
	std::stringstream ss;
	ss << "glfw error occurred. (Error Code: " << error << ")\n" << description;
	logger.severe(ss);
}

void Spark::Window::GLFWWindow::windowResizeCallback(GLFWwindow* window, int width, int height)
{
	dimensions.x = width;
	dimensions.y = height;
	Spark::Events::Types::WindowResize e;
	Spark::Events::callEvent(e);
}

bool Spark::Window::GLFWWindow::createWindow()
{
	auto& logger = SparkInternal::getLogger();
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		logger.severe("Failed to initialise GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), NULL, NULL);
	if (!window) {
		logger.severe("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
		static_cast<GLFWWindow*>(glfwGetWindowUserPointer(win))->windowResizeCallback(win, w, h);
		});

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

void Spark::Window::GLFWWindow::swapBuffers()
{
	glfwSwapBuffers(window);
}