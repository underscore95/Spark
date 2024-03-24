#pragma once

#include "MVP.h"

namespace Spark::Graphics {
	class CameraController;

	class Camera {
	private:
		static constexpr glm::mat4 IDENTITY{ glm::identity<glm::mat4>() };

		MVP mvp;

		glm::vec3 position;
		glm::vec3 rotation;

		CameraController* controller{ nullptr };

		void updateView();
	public:
		Camera(const MVP& mvp);
		~Camera();

		/*
		* Creates an orthographic camera positioned at the origin, looking down the negative z axis.
		*/
		static std::unique_ptr<Camera> ortho(const float left, const float right, const float bottom, const float top, const float zNear = 0.1f, const float zFar = 100.0f);

		/*
		* Creates a perspective camera positioned at the origin, looking down the negative z axis.
		*/
		static std::unique_ptr<Camera> perspective(const float fovY, const glm::vec2 windowDimensions, const float zNear = 0.1f, const float zFar = 100.0f);

		/*
		* Sets the camera controller, destroying any previous controller linked to this camera.
		*/
		void setCameraController(std::unique_ptr<CameraController> controller);

		/*
		* Set the camera position
		*
		* \param position The position
		*/
		void setPosition(const glm::vec3& position);

		/*
		* Set the yaw, pitch, and roll of the camera in degrees
		* 
		* \param rotation The new rotation
		*/
		void setRotationInDegrees(const glm::vec3& rotation);

		/*
		* Set the yaw, pitch, and roll of the camera in radians
		*
		* \param rotation The new rotation
		*/
		void setRotationInRadians(const glm::vec3& rotation);

		/*
		* \return The model view projection matrix for this camera
		*/
		MVP& getMatrix() { return mvp; }

		/*
		* \return The camera position
		*/
		const glm::vec3& getPosition() const { return position; }

		/*
		* \return The camera rotation in radians
		*/
		const glm::vec3& getRotation() const { return rotation; }
	};
}