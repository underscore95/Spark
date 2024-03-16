#pragma once

#include "buffers/VertexArray.h"
#include "shaders/ShaderProgram.h"
#include "pch.h"
#include "window/abstract/Window.h"
#include "graphics/api/camera/Camera.h"

namespace Spark::Graphics {
	class Renderer {
	protected:
		std::shared_ptr<Spark::Window::Window> window;
		std::shared_ptr<Spark::Graphics::Camera> camera;
	public:
		Renderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera)
			: window{ window }, camera{ camera } {};

		void setCamera(std::shared_ptr<Spark::Graphics::Camera> camera) { 
			assert(camera != nullptr);
			this->camera = camera; 
		}
		virtual void draw(const VertexArray& vertexArray, ShaderProgram& shaders) = 0;
		virtual void clear() const = 0;
	};
}