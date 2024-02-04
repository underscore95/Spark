#pragma once

#include <GL/glew.h>
#include <vector>
#include <cassert>
#include "../TypeConverter.h"

namespace GL {
	struct BufferLayoutElement {
		unsigned int index;
		unsigned int count;
		GLenum type;
		bool normalized;
		unsigned int size;
	};

	class BufferLayout {
	private:
		std::vector<BufferLayoutElement> elements; 
		unsigned int stride{ 0 };
	public:
		template<typename T> void push(unsigned int count) {
			const unsigned int elementSize = sizeof(T);
			stride += elementSize * count;
			elements.emplace_back(elements.size(), count, TypeConverter::getGLType<T>(), false, elementSize);
		};

		const unsigned int& getStride() const {
			return stride;
		}

		const std::vector<BufferLayoutElement>& getElements() const {
			return elements;
		}
	};
}