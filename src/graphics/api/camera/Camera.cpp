#include "Camera.h"
#include "Camera.h"
#include "CameraController.h"
#include "logging/Logger.h"
#include "logging/Logging.h"

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

	std::unique_ptr<Camera> Camera::perspective(const float fovY, const glm::vec2 windowDimensions, const float zNear, const float zFar) {
		MVP mvp;
		const auto proj = glm::perspective(fovY, windowDimensions.x / windowDimensions.y, zNear, zFar);
		mvp.setProj(proj); // Scale down to 0 to 1 range
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

		glm::vec3 lookAt;
		lookAt.x = sinY * cosP;
		lookAt.y = sinP;
		lookAt.z = cosP * -cosY;

		// Calculate the right vector
		glm::vec3 rightVector;
		rightVector.x = cosY * cosR - sinY * sinP * sinR;
		rightVector.y = -cosP * sinR;
		rightVector.z = sinY * cosR + sinP * sinR * cosY;

		// Calculate the up vector
		glm::vec3 upVector = glm::cross(rightVector, lookAt);

		auto& l = Spark::getLogger("spark");
		l.info("position: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z));
		l.info("lookAt: " + std::to_string(lookAt.x) + ", " + std::to_string(lookAt.y) + ", " + std::to_string(lookAt.z));
		l.info("upVector: " + std::to_string(upVector.x) + ", " + std::to_string(upVector.y) + ", " + std::to_string(upVector.z));

		mvp.setView(glm::lookAt(position, position + lookAt, glm::normalize(upVector)));
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