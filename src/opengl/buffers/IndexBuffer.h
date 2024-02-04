#pragma once

#include "Buffer.h"

namespace GL {
	class IndexBuffer : public Buffer {
	private:
		unsigned int indicesCount;
	public:
		IndexBuffer(int usageHint, unsigned int indicesCount, unsigned int sizeOfElement, const unsigned int* data)
			: Buffer(GL_ELEMENT_ARRAY_BUFFER, usageHint, indicesCount * sizeOfElement, data), indicesCount{ indicesCount }
		{};

		const unsigned int getCount() const { return indicesCount;  }
	};
}