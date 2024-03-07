#pragma once

#include "graphics/abstract/Renderer.h"

namespace Spark::Graphics::GL {
	class Renderer : public Spark::Graphics::Renderer {
	private:

	public:
		Renderer(std::shared_ptr<Spark::Window::Window> window);

		void draw(const VertexArray& vertexArray, ShaderProgram& shaders) const override;
		void clear() const override;
	};
}