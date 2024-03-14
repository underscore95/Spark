#pragma once

#include "MVP.h"

namespace Spark::Graphics {
	class Camera {
	private:
		static constexpr glm::mat4 IDENTITY{ glm::identity<glm::mat4>() };

		MVP mvp;

		glm::vec3 position;
		glm::vec3 rotation;

		void updateView();
	public:
		Camera(const MVP& mvp);

		/*
		* Creates an orthographic camera positioned at the origin, looking down the positive z axis.
		*/
		static std::unique_ptr<Camera> ortho(const float left, const float right, const float bottom, const float top, const float zNear = 0.1f, const float zFar = 100.0f);

		/*
		* Creates a perspective camera positioned at the origin, looking down the positive z axis.
		*/
		static std::unique_ptr<Camera> perspective(const float fovY, const float aspect, const float zNear = 0.1f, const float zFar = 100.0f);

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
		* Return the model view projection matrix for this camera
		*/
		MVP& getMatrix() { return mvp; }
	};
}