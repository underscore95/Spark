#pragma once

#include "graphics/abstract/IndexBuffer.h"

namespace Spark::Graphics::GL {
	class IndexBuffer :
		public Spark::Graphics::IndexBuffer {
	public:
		IndexBuffer(unsigned int size, unsigned int count, const void* data);
		~IndexBuffer();

		void bind() const override;

		void unbind() const override;

	};
}