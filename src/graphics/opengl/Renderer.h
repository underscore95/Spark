#pragma once

#include "graphics/abstract/Renderer.h"

namespace Spark::Graphics::GL {
	class Renderer : public Spark::Graphics::Renderer {
		void draw(const VertexArray& vertexArray, const ShaderProgram& shaders) const override;
		void clear() const override;
	};
}