#pragma once

#include "CameraController.h"

namespace Spark::Graphics {
	class KeyboardCameraController : public CameraController {
	protected:
		virtual void handleInput(float dt) override;

	public:
		KeyboardCameraController(std::shared_ptr<Camera> camera, Spark::Window::Input& input, const float speed = 100.0f, const float sensitivity = 100.0f)
			: CameraController(camera, input, speed, sensitivity) {}

	};
}