#include "graphics/abstract/buffers/VertexBuffer.h"
#include "graphics/abstract/buffers/IndexBuffer.h"
#include "graphics/abstract/buffers/VertexArray.h"
#include "graphics/abstract/shaders/Shader.h"
#include "graphics/abstract/Renderer.h"
#include "graphics/abstract/textures/Texture.h"
#include "graphics/api/camera/Camera.h"

#include "pch.h"

#include "window/abstract/Window.h"

namespace Spark::Graphics {
	/*
	* \param window The window to render on
	* 
	* \return unique pointer to a renderer
	*/
	std::unique_ptr<Renderer> createRenderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera);

	/*
	* Creates an orthographic camera positioned at the origin, looking down the positive z axis.
	*/
	std::unique_ptr<Camera> ortho(const float left, const float right, const float bottom, const float top, const float zNear = 0.1f, const float zFar = 100.0f);

	/*
	* Creates a perspective camera positioned at the origin, looking down the positive z axis.
	*/
	std::unique_ptr<Camera> perspective(const float fovY, const float aspect, const float zNear = 0.1f, const float zFar = 100.0f);

	/*
	* \return unique pointer to a vertex buffer layout
	*/
	std::unique_ptr<VertexBufferLayout> createVertexBufferLayout();

	/*
	* \param size Size of the data buffer in bytes.
	* \param data Pointer to the data buffer.
	*
	* \return unique pointer to a vertex buffer.
	*/
	std::unique_ptr<VertexBuffer> createVertexBuffer(unsigned int size, const void* data);

	/*
	* \param size Size of the data buffer in bytes.
	* \param count Number of elements in the data
	* \param data Pointer to the data buffer.
	*
	* \return unique pointer to an index buffer.
	*/
	std::unique_ptr<IndexBuffer> createIndexBuffer(unsigned int size, unsigned int count, const void* data);

	/*
	* \param indexBuffer The index buffer
	* \param vertexBuffer The vertex buffer
	* \param vertexBufferLayout The vertex buffer layout
	*
	* \return unique pointer to a vertex array.
	*/
	std::unique_ptr<VertexArray> createVertexArray(std::unique_ptr<IndexBuffer> indexBuffer,
		std::unique_ptr<VertexBuffer> vertexBuffer, std::unique_ptr<VertexBufferLayout> vertexBufferLayout);

	/*
	* \param filePath Path to the shader source code, relative to your game executable.
	*
	* \return unique pointer to a shader.
	*/
	std::unique_ptr<Shader> createVertexShader(const std::string filePath);

	/*
	* \param filePath Path to the shader source code, relative to your game executable.
	*
	* \return unique pointer to a shader.
	*/
	std::unique_ptr<Shader> createFragmentShader(const std::string filePath);

	/*
	* \param shaders Vector of shaders to add to this program.
	*
	* \return unique pointer to a shader program.
	*/
	std::unique_ptr<ShaderProgram> createShaderProgram(const std::vector<Shader>& shaders);

	/*
	* \param filePath Path to the image file, relative to your game executable.
	*
	* \return unique pointer to a texture.
	*/
	std::unique_ptr<Texture> loadTexture(const std::string& filePath);
}

namespace SparkInternal::Graphics {
	void init();
}