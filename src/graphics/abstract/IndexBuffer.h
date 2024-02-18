#pragma once

#include "Buffer.h"

namespace Spark::Graphics {
	class IndexBuffer :
		public Buffer {
	private:
		unsigned int count;
	public:
		/*
		* \param size Size of the data buffer in bytes.
		* \param count Number of elements in the data
		* \param data Pointer to the data buffer.
		*/
		IndexBuffer(unsigned int size, unsigned int count, const void* data) : Buffer(size, data), count{ count } {}

		const unsigned int getCount() const { return count; }
	};
}