#pragma once

#include "CameraController.h"

namespace Spark::Graphics {
	class KeyboardCameraController : public CameraController {
	protected:
		virtual void handleInput(float dt) override;
	};
}