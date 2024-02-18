#pragma once

#include "Buffer.h"

namespace Spark::Graphics {
	class VertexBuffer :
		public Buffer {
	public:
		/*
		* \param size Size of the data buffer in bytes.
		* \param data Pointer to the data buffer.
		*/
		VertexBuffer(unsigned int size, const void* data) : Buffer(size, data) {}
	};
}