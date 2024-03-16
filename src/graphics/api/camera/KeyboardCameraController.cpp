#include "KeyboardCameraController.h"
#include "pch.h"

void Spark::Graphics::KeyboardCameraController::handleInput(float dt)
{
	glm::vec3 dp(
		input.isKeyDown(Spark::Window::Keyboard::D) - input.isKeyDown(Spark::Window::Keyboard::A), 
		input.isKeyDown(Spark::Window::Keyboard::SPACE) - input.isKeyDown(Spark::Window::Keyboard::LEFT_SHIFT),
		input.isKeyDown(Spark::Window::Keyboard::S) - input.isKeyDown(Spark::Window::Keyboard::W)
	);
	dp *= (dt * speed);

	camera->setPosition(camera->getPosition() + dp);

	glm::vec3 dr(
		input.isKeyDown(Spark::Window::Keyboard::RIGHT) - input.isKeyDown(Spark::Window::Keyboard::LEFT),
		input.isKeyDown(Spark::Window::Keyboard::UP) - input.isKeyDown(Spark::Window::Keyboard::DOWN),
		0
	);
	dr *= (dt * sensitivity);

	camera->setRotationInRadians(camera->getRotation() + dr);
}
