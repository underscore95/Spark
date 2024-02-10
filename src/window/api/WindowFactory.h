#pragma once

#include "window/abstract/Window.h"

#include "pch.h"

namespace Spark::Window {
	std::unique_ptr<Window> create(const std::string& title = "My Spark Game", const glm::uvec2& dimensions = glm::uvec2(1280, 720));
}