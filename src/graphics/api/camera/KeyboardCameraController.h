#pragma once

#include "CameraController.h"

namespace Spark::Graphics {
	class KeyboardCameraController : public CameraController {
	public:
		virtual void handleInput(float dt) override;
	};
}