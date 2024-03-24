#pragma once

#include "CameraController.h"

namespace Spark::Graphics {
	class KeyboardCameraController : public CameraController {
	protected:
		virtual void handleInput(float dt) override;

	public:
		KeyboardCameraController(std::shared_ptr<Camera> camera, Spark::Window::Input& input, const float speed, const float sensitivity)
			: CameraController(camera, input, speed, sensitivity) {}

	};
}