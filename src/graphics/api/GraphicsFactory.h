#include "graphics/abstract/buffers/VertexBuffer.h"
#include "graphics/abstract/buffers/IndexBuffer.h"
#include "graphics/abstract/buffers/VertexArray.h"
#include "graphics/abstract/shaders/Shader.h"
#include "graphics/abstract/Renderer.h"
#include "graphics/abstract/MVP.h"

#include "pch.h"

namespace Spark::Graphics {
	/*
	* Note that this is not passed into any shader programs automatically.
	* \return valid reference to the main model view projection matrix.
	*/
	MVP& getMVP();

	/*
	* \return valid const reference to the main renderer.
	*/
	const Renderer& getRenderer();

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
	std::unique_ptr<VertexArray> createVertexArray(const std::shared_ptr<IndexBuffer> indexBuffer, 
		const std::shared_ptr<VertexBuffer> vertexBuffer, const std::shared_ptr<VertexBufferLayout> vertexBufferLayout);

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
}

namespace SparkInternal::Graphics {
	void init();
}