#include "GraphicsFactory.h"

#ifdef _WIN32
#include "graphics/opengl/Renderer.h"
#include "graphics/opengl/buffers/IndexBuffer.h"
#include "graphics/opengl/buffers/VertexBuffer.h"
#include "graphics/opengl/buffers/VertexBufferLayout.h"
#include "graphics/opengl/buffers/VertexArray.h"
#include "graphics/opengl/shaders/FragmentShader.h"
#include "graphics/opengl/shaders/VertexShader.h"
#include "graphics/opengl/shaders/ShaderProgram.h"
#include "graphics/opengl/textures/Texture.h"
#endif

namespace Spark::Graphics {
	std::unique_ptr<Renderer> createRenderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::Renderer>(window, camera);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<Camera> ortho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
	{
		return std::move(Spark::Graphics::Camera::ortho(left, right, bottom, top, zNear, zFar));
	}

	std::unique_ptr<Camera> perspective(const float fovY, const glm::vec2 windowDimensions, const float zNear, const float zFar)
	{
		return std::move(Spark::Graphics::Camera::perspective(fovY, windowDimensions, zNear, zFar));
	}

	std::unique_ptr<VertexBufferLayout> createVertexBufferLayout()
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexBufferLayout>();
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<VertexBuffer> createVertexBuffer(unsigned int size, const void* data)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexBuffer>(size, data);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<IndexBuffer> createIndexBuffer(unsigned int size, unsigned int count, const void* data)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::IndexBuffer>(size, count, data);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<VertexArray> createVertexArray(std::shared_ptr<IndexBuffer> indexBuffer,
		std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<VertexBufferLayout> vertexBufferLayout)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexArray>(indexBuffer, std::move(vertexBuffer), vertexBufferLayout);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<Shader> createVertexShader(const std::string filePath)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexShader>(filePath);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<Shader> createFragmentShader(const std::string filePath)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::FragmentShader>(filePath);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<ShaderProgram> createShaderProgram(const std::vector<Shader>& shaders)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::ShaderProgram>(shaders);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<Texture> loadTexture(const std::string& filePath)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::Texture>(filePath);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}
}