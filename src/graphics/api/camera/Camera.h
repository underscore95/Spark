#pragma once

#include "MVP.h"

namespace Spark::Window {
	class Window;
}

namespace Spark::Graphics {
	class CameraController;

	class Camera {
	private:
		static constexpr glm::mat4 IDENTITY{ glm::identity<glm::mat4>() };
		static constexpr float NONE = FLT_MIN;

		MVP mvp;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;

		float fovY;

		float zNear;
		float zFar;

		float scaleOrthographic{ 1.0f };

		CameraController* controller{ nullptr };
		std::shared_ptr<Spark::Window::Window> window{ nullptr };

		void updateView();
	public:
		/*
		* Use ortho() and perspective() static methods in this class to construct an instance, it is easier.
		*/
		Camera(const MVP& mvp, float fovY = NONE, float zNear = 0.1f, float zFar = 100.0f);
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
		* Link to a window, and each frame the projection matrix will be updated to be equal to the window dimensions.
		* You must have a camera controller attached.
		*
		* \param window Window
		* \param scaleOrthographic Right & bottom values will be multiplied by this
		*/
		void linkWindow(std::shared_ptr<Spark::Window::Window> window, const float scaleOrthographic = 1.0f / 1000.0f);

		/*
		* Update the projection matrix using the window. Fails silently if window isn't linked.
		*/
		void updateProjectionMatrix();

		bool isPerspectiveCamera() const;

		/*
		* Sets the camera controller, destroying any previous controller linked to this camera.
		*/
		void setCameraController(std::unique_ptr<CameraController> controller);

		/*
		* Update the projection matrix to be an orthographic projection.
		* See GraphicsFactory.ortho
		*/
		void setOrthographicProjection(const float left, const float right, const float bottom, const float top, const float zNear = 0.1f, const float zFar = 100.0f);

		/*
		* Update the orthographic projection matrix with a new window size.
		* This will force `left` and `top` to be 0.
		*/
		void updateOrthographicProjection(const glm::vec2& windowDimensions);

		/*
		* Update the projection matrix to be a perspective projection.
		*
		* See GraphicsFactory.perspective
		*/
		void setPerspectiveProjection(const float fovY, const glm::vec2 windowDimensions, const float zNear = 0.1f, const float zFar = 100.0f);

		/*
		* Update the perspective projection matrix with a new window size.
		*/
		void updatePerspectiveProjection(const glm::vec2& windowDimensions);

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

		/*
		* \return A normalised vector pointing in the camera's up direction
		*/
		const glm::vec3& getUp() const { return up; }

		/*
		* \return A normalised vector pointing in the camera's forward direction
		*/
		const glm::vec3& getForward() const { return forward; }

		/*
		* \return A normalised vector pointing in the camera's right direction
		*/
		const glm::vec3& getRight() const { return right; }
	};
}