#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "shaders/ShaderProgram.h"

namespace GL {
	class Renderer {
	private:

	public:
		void draw(const VertexArray& vertexArray, const ShaderProgram& shader);
		
		void clearFrame();
	};
}