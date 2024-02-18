#pragma once

#include "graphics/abstract/VertexBuffer.h"

namespace Spark::Graphics::GL {
	class VertexBuffer :
		public Spark::Graphics::VertexBuffer {
	public:
		VertexBuffer(unsigned int size, const void* data);
		~VertexBuffer();

		void bind() const override;

		void unbind() const override;

	};
}