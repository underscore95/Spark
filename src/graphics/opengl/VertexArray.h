#pragma once

#include "graphics/abstract/VertexArray.h"

namespace Spark::Graphics::GL {
	class VertexArray :
		public Spark::Graphics::VertexArray {
	private:
		unsigned int rendererId;
	public:
		VertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<VertexBufferLayout>& vertexBufferLayout);
		~VertexArray();

		void bind() const override;
		void unbind() const override;
	};
}