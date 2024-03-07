#pragma once

#include "buffers/VertexArray.h"
#include "shaders/ShaderProgram.h"
#include "pch.h"
#include "window/abstract/Window.h"

namespace Spark::Graphics {
	class Renderer {
	protected:
		std::shared_ptr<Spark::Window::Window> window;
	public:
		Renderer(std::shared_ptr<Spark::Window::Window> window) : window{ window } {};

		virtual void draw(const VertexArray& vertexArray, ShaderProgram& shaders) const = 0;
		virtual void clear() const = 0;
	};
}