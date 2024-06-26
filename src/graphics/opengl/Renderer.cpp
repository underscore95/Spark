#include "Renderer.h"
#include "Renderer.h"
#include "Renderer.h"
#include <GL/glew.h>
#include "pch.h"
#include "logging/Logger.h"
#include "logging/Logging.h"
#include <GLFW/glfw3.h>

static void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string sourceStr, typeStr, severityStr;

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: severityStr = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM: severityStr = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW: severityStr = "Low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: return;// severityStr = "Notification"; break;
	default: severityStr = "Unknown"; break;
	}

	switch (source) {
	case GL_DEBUG_SOURCE_API: sourceStr = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceStr = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: sourceStr = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION: sourceStr = "Application"; break;
	default: sourceStr = "Unknown"; break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR: typeStr = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeStr = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY: typeStr = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE: typeStr = "Performance"; break;
	case GL_DEBUG_TYPE_OTHER: typeStr = "Other"; break;
	default: typeStr = "Unknown"; break;
	}

	std::stringstream ss;
	ss << "[OpenGL Error] ID: " << id << ", Source: " << sourceStr << ", Type: " << typeStr << ", Severity: " << severityStr << "\n" << std::string(message, length);

	auto& logger = SparkInternal::getLogger();
	logger.severe(ss);
}

Spark::Graphics::GL::Renderer::Renderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera)
	: Spark::Graphics::Renderer(window, camera)
{
	auto& logger = SparkInternal::getLogger();
	logger.info("Initialising OpenGL...");

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::stringstream ss;
		ss << "Failed to initialise OpenGL, glewInit error: " << (char*)glewGetErrorString(err);
		logger.severe(ss);
	}

	logger.info("Initialised OpenGL!");

	{
		std::stringstream ss;
		ss << "OpenGL Version " << (char*)glGetString(GL_VERSION);
		logger.info(ss);
	}

	{
		std::stringstream ss;
		ss << "GLEW Version " << (char*)glewGetString(GLEW_VERSION);
		logger.info(ss);
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorCallback, 0);

	window->setSwapInterval(1);

	//glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}

void Spark::Graphics::Renderer::startDrawing(std::shared_ptr<Material> material)
{
	assert(material != nullptr);
	clear();
	this->material = material;
	this->material->bind();

}

void Spark::Graphics::GL::Renderer::draw(const Spark::Graphics::VertexArray& vertexArray)
{
	assert(material != nullptr);
	vertexArray.bind();

	material->getShaders().setUniformMat4f("Sp_MVP", camera->getMatrix().getMVP());

	glDrawElements(GL_TRIANGLES, vertexArray.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void Spark::Graphics::GL::Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
}

void Spark::Graphics::Renderer::renderModel(const Model& model)
{
	for (const auto& segment : model.getSegments()) {
		startDrawing(segment.material);
		draw(*(segment.vertexArray));
		stopDrawing();
	}
}
