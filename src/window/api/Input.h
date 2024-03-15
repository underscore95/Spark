#pragma once

#include "pch.h"

namespace Spark::Window {
	class Window;
	class GLFWWindow;

	class Input {
	private:
		Spark::Window::Window* window;

		glm::dvec2 mousePosition;

		Input(Spark::Window::Window* window) : window{ window } {};

		friend class Spark::Window::Window;
		friend class Spark::Window::GLFWWindow;

	public:
		/*
		* \return The mouse position, where top left corner of the window is 0,0. Position may be outside the window.
		*/
		[[nodiscard]] constexpr const glm::vec2& getMousePos() const { return mousePosition; }

		/*
		* \return The mouse position, clamped to inside the window.
		*/
		[[nodiscard]] constexpr const glm::vec2 getClampedMousePos() const;
	};
}