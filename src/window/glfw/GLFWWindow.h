#pragma once

#include "window/abstract/Window.h"
#include <GLFW/glfw3.h>

namespace Spark::Window {
	class GLFWWindow : public Window {
	private:
		GLFWwindow* window;
		bool shouldClose{ false };

		void windowResizeCallback(GLFWwindow* window, int width, int height);

	protected:
		bool createWindow() override;

	public:
		~GLFWWindow();
		GLFWWindow(const std::string& title = "My Spark Game", const glm::uvec2& dimensions = glm::uvec2(1280,720));

		void update() override;

		void setTitle(const std::string& title) override;
		void setDimensions(const glm::uvec2& dimensions) override;

		void swapBuffers() override;
	};
}