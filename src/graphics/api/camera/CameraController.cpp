#include "CameraController.h"
#include "pch.h"
#include "Camera.h"

std::vector<Spark::Graphics::CameraController*> controllers;

void SparkInternal::Graphics::CameraControllerManager::handleInput(float dt)
{
	for (auto controller : controllers) {
		if (controller->isEnabled()) { 
			controller->handleInput(dt); 
		}
	}
}

void SparkInternal::Graphics::CameraControllerManager::update(float dt)
{
	for (auto controller : controllers) {
		if (controller->isEnabled()) {
			controller->update(dt);
		}
		
		if (controller->belongsToCamera) {
			controller->camera->updateProjectionMatrix();
		}
	}
}

Spark::Graphics::CameraController::CameraController(std::shared_ptr<Camera> camera, Spark::Window::Input& input, const float speed, const float sensitivity)
	: camera{ camera }, input{ input }, speed{ speed }, sensitivity{ sensitivity } {
	assert(camera != nullptr);
	assert(speed >= 0);
	assert(sensitivity >= 0);

	controllers.push_back(this);
}

Spark::Graphics::CameraController::~CameraController()
{
	auto it = std::find(controllers.begin(), controllers.end(), this);
	if (it != controllers.end()) {
		controllers.erase(it);
	}
}
