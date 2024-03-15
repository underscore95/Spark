#pragma once

#include "pch.h"
#include "KeysAndButtons.h"

namespace Spark::Window {
	class Window;
	class GLFWWindow;

	class Input {
	private:
		Spark::Window::Window* window;

		glm::dvec2 mousePosition;
		std::unordered_set<Spark::Window::Mouse::MouseButton> mouseButtonsPressed;
		std::unordered_set<Spark::Window::Mouse::MouseButton> mouseButtonsPressedLastFrame;

		std::unordered_set<Spark::Window::Keyboard::Key> keysPressed;
		std::unordered_set<Spark::Window::Keyboard::Key> keysPressedLastFrame;

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
		* \param button The button
		* \return True if the mouse button is currently down
		*/
		[[nodiscard]] const bool isMouseButtonDown(const Spark::Window::Mouse::MouseButton button) const
		{
			return mouseButtonsPressed.contains(button);
		}

		/*
		* \param button The button
		* \return True if the mouse button was just pressed this frame
		*/
		[[nodiscard]] const bool isMouseButtonPressed(const Spark::Window::Mouse::MouseButton button) const
		{
			return isMouseButtonDown(button) && !mouseButtonsPressedLastFrame.contains(button);
		}

		/*
		* \param key The key
		* \return True if the key is currently down
		*/
		[[nodiscard]] const bool isKeyDown(const Spark::Window::Keyboard::Key key) const
		{
			return keysPressed.contains(key);
		}

		/*
		* \param key The key
		* \return True if the key was just pressed this frame
		*/
		[[nodiscard]] const bool isKeyPressed(const Spark::Window::Keyboard::Key key) const
		{
			return isKeyDown(key) && !keysPressedLastFrame.contains(key);
		}
	};
}