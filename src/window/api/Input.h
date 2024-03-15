#pragma once

#include "pch.h"

namespace Spark::Window {
	class Window;
	class GLFWWindow;

	enum class MouseButton {
		LEFT, RIGHT
	};

	class Input {
	private:
		Spark::Window::Window* window;

		glm::dvec2 mousePosition;
		std::unordered_set<MouseButton> mouseButtonsPressed;
		std::unordered_set<MouseButton> mouseButtonsPressedLastFrame;

		void setMouseButtonPressed(MouseButton button);

		void handleInputSetup();

		Input(Spark::Window::Window* window) : window{ window }, mousePosition(0, 0) {};

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

		/*
		* \return True if the mouse button is currently down
		*/
		[[nodiscard]] const bool isMouseButtonDown(const MouseButton button) const { return mouseButtonsPressed.contains(button); }

		/*
		* \return True if the mouse button was just pressed this frame
		*/
		[[nodiscard]] const bool isMouseButtonPressed(const MouseButton button) const { return isMouseButtonDown(button) && !mouseButtonsPressedLastFrame.contains(button); }
	};
}