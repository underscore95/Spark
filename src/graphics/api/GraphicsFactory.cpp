#include "GraphicsFactory.h"

#ifdef _WIN32
#include "graphics/opengl/Renderer.h"
#include "graphics/opengl/buffers/IndexBuffer.h"
#include "graphics/opengl/buffers/VertexBuffer.h"
#include "graphics/opengl/buffers/VertexArray.h"
#include "graphics/opengl/shaders/FragmentShader.h"
#include "graphics/opengl/shaders/VertexShader.h"
#include "graphics/opengl/shaders/ShaderProgram.h"
#endif

namespace SparkInternal::Graphics {
	std::unique_ptr<Spark::Graphics::MVP> mvp;

	void init()
	{
		mvp = std::make_unique<Spark::Graphics::MVP>();
	}
}

namespace Spark::Graphics {
	MVP& getMVP()
	{
		return *SparkInternal::Graphics::mvp;
	}

	std::unique_ptr<Renderer> createRenderer(Spark::Window::Window& window)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::Renderer>();
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

	std::unique_ptr<VertexArray> createVertexArray(std::unique_ptr<IndexBuffer> indexBuffer,
		std::unique_ptr<VertexBuffer> vertexBuffer, std::unique_ptr<VertexBufferLayout> vertexBufferLayout)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexArray>(std::move(indexBuffer), std::move(vertexBuffer), std::move(vertexBufferLayout));
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
}