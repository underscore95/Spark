#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "CameraController.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

namespace Spark::Graphics {
	Camera::Camera(const MVP& mvp, float fovY, float zNear, float zFar) :
		mvp{ mvp }, position{ 0,0,0 }, rotation{ 0,0,0 }, forward{ 0,0,0 }, up{ 0,0,0 }, right{ 0,0,0 },
		fovY{ fovY }, zNear{ zNear }, zFar{ zFar }
	{
		updateView();
	}

	Camera::~Camera()
	{
		if (controller) {
			delete controller;
		}
	}

	std::unique_ptr<Camera> Camera::ortho(const float left, const float right, const float bottom, const float top,
		const float zNear, const float zFar) {
		MVP mvp;
		mvp.setProj(glm::ortho(left, right, bottom, top, zNear, zFar));
		return std::unique_ptr<Camera>(new Camera(mvp));
	}

	std::unique_ptr<Camera> Camera::perspective(const float fovY, const glm::vec2 windowDimensions, const float zNear, const float zFar) {
		MVP mvp;
		const auto proj = glm::perspective(fovY, windowDimensions.x / windowDimensions.y, zNear, zFar);
		mvp.setProj(proj);
		return std::unique_ptr<Camera>(new Camera(mvp, fovY, zNear, zFar));
	}

	void Camera::setCameraController(std::unique_ptr<CameraController> controller)
	{

		this->controller = controller.release();
		this->controller->belongsToCamera = true;
	}

	void Camera::setOrthographicProjection(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
	{
		mvp.setProj(glm::ortho(left, right, bottom, top, zNear, zFar));
		this->fovY = NONE;
		this->zNear = NONE;
		this->zFar = NONE;
	}

	void Camera::setPerspectiveProjection(const float fovY, const glm::vec2 windowDimensions, const float zNear, const float zFar)
	{
		this->fovY = fovY;
		this->zNear = zNear;
		this->zFar = zFar;
		updatePerspectiveProjection(windowDimensions);
	}

	void Camera::updatePerspectiveProjection(const glm::vec2& windowDimensions)
	{
		mvp.setProj(glm::perspective(fovY, windowDimensions.x / windowDimensions.y, zNear, zFar));
	}

	void Camera::updateView()
	{
		auto& l = SparkInternal::getLogger();

		// yaw, pitch, roll
		const float cosY = cosf(rotation.x);
		const float cosP = cosf(rotation.y);
		const float cosR = cosf(rotation.z);
		const float sinY = sinf(rotation.x);
		const float sinP = sinf(rotation.y);
		const float sinR = sinf(rotation.z);

		forward.x = sinY * cosP;
		forward.y = sinP;
		forward.z = cosP * -cosY;
		forward = glm::normalize(forward);

		// Calculate the right vector
		right.x = cosY * cosR - sinY * sinP * sinR;
		right.y = -cosP * sinR;
		right.z = sinY * cosR + sinP * sinR * cosY;
		right = glm::normalize(right);

		// Calculate the up vector
		up = glm::cross(right, forward);
		up = glm::normalize(up);

		mvp.setView(glm::lookAt(position, position + forward, up));
	}

	void Camera::setPosition(const glm::vec3& position)
	{
		this->position = position;
		updateView();
	}

	void Camera::setRotationInDegrees(const glm::vec3& rotation)
	{
		this->rotation.x = glm::radians(rotation.x);
		this->rotation.y = glm::radians(rotation.y);
		this->rotation.z = glm::radians(rotation.z);
		updateView();
	}

	void Camera::setRotationInRadians(const glm::vec3& rotation)
	{
		this->rotation = rotation;
		updateView();
	}
}