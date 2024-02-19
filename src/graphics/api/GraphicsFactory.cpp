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
	std::unique_ptr<Spark::Graphics::Renderer> renderer;

	void createRenderer()
	{
#ifdef _WIN32
		renderer = std::make_unique<Spark::Graphics::GL::Renderer>();
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}
}

namespace Spark::Graphics {
	const Renderer& getRenderer()
	{
		return *SparkInternal::Graphics::renderer;
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

	std::unique_ptr<VertexArray> createVertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<VertexBufferLayout>& vertexBufferLayout)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexArray>(indexBuffer, vertexBuffer, vertexBufferLayout);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<Shader> createVertexShader(const std::string& filePath)
	{
#ifdef _WIN32
		return std::make_unique<Spark::Graphics::GL::VertexShader>(filePath);
#else
		throw std::runtime_error("No graphics implementations for this platform.");
#endif
	}

	std::unique_ptr<Shader> createFragmentShader(const std::string& filePath)
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