#include "KeyboardCameraController.h"
#include "pch.h"

void Spark::Graphics::KeyboardCameraController::handleInput(float dt)
{
	// Note this class could be implemented much more efficiently

	glm::vec3 dp(0.0f); // Delta position

	// Forward and backward
	if (input.isKeyDown(Spark::Window::Keyboard::W)) {
		dp += camera->getForward();
	}
	if (input.isKeyDown(Spark::Window::Keyboard::S)) {
		dp -= camera->getForward();
	}

	// Right and left 
	if (input.isKeyDown(Spark::Window::Keyboard::D)) {
		dp += camera->getRight();
	}
	if (input.isKeyDown(Spark::Window::Keyboard::A)) {
		dp -= camera->getRight();
	}

	// Up and down 
	if (input.isKeyDown(Spark::Window::Keyboard::SPACE)) {
		dp += camera->getUp();
	}
	if (input.isKeyDown(Spark::Window::Keyboard::LEFT_SHIFT)) {
		dp -= camera->getUp();
	}

	if (glm::length(dp) > 0) {
		dp = glm::normalize(dp) * (dt * speed);
		camera->setPosition(camera->getPosition() + dp);
	}

	glm::vec3 dr(0.0f); // Delta rotation
	if (input.isKeyDown(Spark::Window::Keyboard::RIGHT)) {
		dr.x += 1.0f;
	}
	if (input.isKeyDown(Spark::Window::Keyboard::LEFT)) {
		dr.x -= 1.0f;
	}
	if (input.isKeyDown(Spark::Window::Keyboard::UP)) {
		dr.y += 1.0f;
	}
	if (input.isKeyDown(Spark::Window::Keyboard::DOWN)) {
		dr.y -= 1.0f;
	}

	if (glm::length(dr) > 0) {
		dr = glm::normalize(dr) * (dt * sensitivity);
		camera->setRotationInRadians(camera->getRotation() + dr);
	}

	camera->setRotationInRadians(camera->getRotation() + dr);
}
