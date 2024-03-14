#pragma once

#include "graphics/abstract/Renderer.h"

namespace Spark::Graphics::GL {
	class Renderer : public Spark::Graphics::Renderer {
	private:

	public:
		Renderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera);

		void draw(const Spark::Graphics::VertexArray& vertexArray, Spark::Graphics::ShaderProgram& shaders) override;
		void clear() const override;
	};
}