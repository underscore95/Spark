#pragma once

#include "window/api/Input.h"
#include "graphics/api/camera/Camera.h"

namespace Spark::Graphics {
	class CameraController {
	protected:
		std::shared_ptr<Camera> camera;
		Spark::Window::Input& input;
		float speed;
		float sensitivity;
		bool enabled = true;

		virtual void handleInput(float dt) = 0;
	public:
		/*
		* \param camera A shared ptr to the camera to control
		* \param input A reference to the input class to use
		* \param speed Speed to move, defaults to 100.
		* \param sensitivity Speed to rotate, defaults to 100.
		*/
		CameraController(std::shared_ptr<Camera> camera, Spark::Window::Input& input, const float speed = 100.0f, const float sensitivity = 100.0f)
			: camera{ camera }, input{ input }, speed{ speed }, sensitivity{ sensitivity } {
			assert(camera != nullptr);
			assert(speed >= 0);
			assert(sensitivity >= 0);
		}

		[[nodiscard]] constexpr const bool isEnabled() const { return enabled; }
		constexpr void enable() { enabled = true; }
		constexpr void disable() { enabled = false; }
	};
}