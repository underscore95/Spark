#include "Camera.h"
#include "Camera.h"
#include "CameraController.h"

namespace Spark::Graphics {
	Camera::Camera(const MVP& mvp) :
		mvp{ mvp }, position{ 0,0,0 }, rotation{ 0,0,0 }
	{
		updateView();
	}

	Camera::~Camera()
	{
		delete controller;
	}

	std::unique_ptr<Camera> Camera::ortho(const float left, const float right, const float bottom, const float top,
		const float zNear, const float zFar) {
		MVP mvp;
		mvp.setProj(glm::ortho(left, right, bottom, top, zNear, zFar));
		return std::unique_ptr<Camera>(new Camera(mvp));
	}

	std::unique_ptr<Camera> Camera::perspective(const float fovY, const float aspect, const float zNear, const float zFar) {
		MVP mvp;
		mvp.setProj(glm::perspective(fovY, aspect, zNear, zFar));
		return std::unique_ptr<Camera>(new Camera(mvp));
	}

	void Camera::setCameraController(std::unique_ptr<CameraController> controller)
	{

		this->controller = controller.release();
		this->controller->belongsToCamera = true;
	}

	void Camera::updateView()
	{
		// yaw, pitch, roll
		const float cosY = cosf(rotation.x);
		const float cosP = cosf(rotation.y);
		const float cosR = cosf(rotation.z);
		const float sinY = sinf(rotation.x);
		const float sinP = sinf(rotation.y);
		const float sinR = sinf(rotation.z);

		glm::vec3 lookAt = position;
		lookAt.x += sinY * cosP;
		lookAt.y += sinP;
		lookAt.z += cosP * -cosY;

		glm::vec3 upVector(0, 0, 0);
		upVector.x = -cosY * sinR - sinY * sinP * cosR;
		upVector.y = cosP * cosR;
		upVector.z = -sinY * sinR - sinP * cosR * -cosY;

		mvp.setView(glm::lookAt(position, glm::normalize(lookAt), glm::normalize(upVector)));
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