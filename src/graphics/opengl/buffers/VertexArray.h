#pragma once

#include "graphics/abstract/buffers/VertexArray.h"

namespace Spark::Graphics::GL {
	class VertexArray :
		public Spark::Graphics::VertexArray {
	private:
		unsigned int rendererId;

		void init();
	public:
		VertexArray(std::shared_ptr<Spark::Graphics::IndexBuffer> indexBuffer,
			std::unique_ptr<Spark::Graphics::VertexBuffer> vertexBuffer,
			std::shared_ptr<Spark::Graphics::VertexBufferLayout> vertexBufferLayout);
		~VertexArray();

		void bind() const override;
		void unbind() const override;
	};
}