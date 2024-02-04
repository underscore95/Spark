#pragma once

#include "Buffer.h"

namespace GL {
	class VertexBuffer : public Buffer {
	public:
		VertexBuffer(int usageHint, int size, const void* data) : Buffer(GL_ARRAY_BUFFER, usageHint, size, data) {};
	};
}