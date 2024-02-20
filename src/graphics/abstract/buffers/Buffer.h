#pragma once

namespace Spark::Graphics {
	/*
	* Parent class for IndexBuffer and VertexBuffer
	*/
	class Buffer {
	protected:
		unsigned int size;
		const void* data;
		unsigned int rendererId;
	public:
		/*
		* \param size Size of the data buffer in bytes.
		* \param data Pointer to the data buffer.
		*/
		Buffer(unsigned int size, const void* data) : size{ size }, data{ data }, rendererId{ 0 } {}
		~Buffer() { delete[] data; }

		const unsigned int getRendererId() const { return rendererId; }

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}