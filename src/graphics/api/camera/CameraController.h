#pragma once

#include "window/api/Input.h"
#include "graphics/api/camera/Camera.h"

namespace SparkInternal::Graphics {
	class CameraControllerManager {
	private:
		CameraControllerManager() {};
	public:
		void handleInput(float dt);
		void update(float dt);

		[[nodiscard]] static CameraControllerManager& singleton() {
			static CameraControllerManager inst;
			return inst;
		}
	};
}

namespace Spark::Graphics {
	class CameraController {
	private:
		bool belongsToCamera = false;

		friend class Camera;
	protected:
		std::shared_ptr<Camera> camera;
		Spark::Window::Input& input;
		float speed;
		float sensitivity;
		bool enabled = true;

		virtual void handleInput(float dt) {};
		virtual void update(float dt) {};
		friend class SparkInternal::Graphics::CameraControllerManager;
	public:
		/*
		* \param camera A shared ptr to the camera to control
		* \param input A reference to the input class to use
		* \param speed Speed to move
		* \param sensitivity Speed to rotate
		*/
		CameraController(std::shared_ptr<Camera> camera, Spark::Window::Input& input, const float speed, const float sensitivity);
		~CameraController();

		[[nodiscard]] constexpr const bool isEnabled() const { return enabled && belongsToCamera; }
		constexpr void enable() { enabled = true; }
		constexpr void disable() { enabled = false; }
	};
}