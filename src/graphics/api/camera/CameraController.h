#pragma once

#include "window/api/Input.h"
#include "graphics/api/camera/Camera.h"

namespace Spark::Graphics {
	class CameraController {
	protected:
		std::shared_ptr<Camera> camera;
		Spark::Window::Input& input;
	public:
		CameraController(std::shared_ptr<Camera> camera, Spark::Window::Input& input) : camera{ camera }, input{ input } {}

		virtual void handleInput(float dt) = 0;
	};
}