#pragma once

#include <GL/glew.h>
#include "BufferLayout.h"

namespace GL {
	class Buffer {
	private:
		int type;
		int usageHint;
		unsigned int size;
		const void* data;
		unsigned int id;
	public:
		Buffer(int type, int usageHint, unsigned int size, const void* data);
		~Buffer();

		const unsigned int getId() const;

		virtual void bind() const;
		virtual void unbind() const;
	};
}