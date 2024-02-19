#pragma once

#include "buffers/VertexArray.h"
#include "shaders/ShaderProgram.h"
#include "pch.h"

namespace Spark::Graphics {
	class Renderer {
	private:
		
	public:
		virtual void draw(const VertexArray& vertexArray, const ShaderProgram& shaders) const = 0;
		virtual void clear() const = 0;
	};

	inline std::unique_ptr<Renderer> renderer;
}