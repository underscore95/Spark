#include "Application.h"

Spark::Application::Application() {

}

Spark::Application::~Application() {

}

void Spark::Application::stop()
{
	running = false;
}

const bool Spark::Application::isRunning() const
{
	return running;
}
