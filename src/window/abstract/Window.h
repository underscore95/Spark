#pragma once

#include "pch.h"
#include <glm/glm.hpp>

namespace Spark::Window {
	class Window {
	private:

	protected:
		std::string title;
		glm::uvec2 dimensions;
		bool successfullyInitialised{ false };
		bool windowClosed{ false };

		virtual bool createWindow() = 0;

	public:
		Window(const std::string& title, const glm::uvec2& dimensions = glm::uvec2(1280, 720));
		Window(const Window& copy) = delete;

		virtual void update() = 0;

		// Returns true if the window was successfully initialised and opened
		const bool isSuccessfullyInitialised() const;
		const std::string& getTitle() const;
		const glm::uvec2 getDimensions() const;
		// Returns true if the window has been opened and is now closed
		const bool isWindowClosed() const;
		// Returns true if the window is currently open, returns false if the window has been closed or if the window was never opened
		const bool isWindowOpen() const;

		virtual void setTitle(const std::string& title) = 0;
		virtual void setDimensions(const glm::uvec2& dimensions) = 0;
		
		virtual void swapBuffers() = 0;
	};
}