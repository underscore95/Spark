#pragma once

#include "buffers/VertexArray.h"
#include "shaders/ShaderProgram.h"
#include "pch.h"
#include "window/abstract/Window.h"
#include "graphics/api/camera/Camera.h"
#include "Material.h"

namespace Spark::Graphics {
	class Renderer {
	protected:
		std::shared_ptr<Spark::Window::Window> window;
		std::shared_ptr<Spark::Graphics::Camera> camera;
		std::shared_ptr<Material> material;
	public:
		Renderer(std::shared_ptr<Spark::Window::Window> window, std::shared_ptr<Spark::Graphics::Camera> camera)
			: window{ window }, camera{ camera } {};

		void setCamera(std::shared_ptr<Spark::Graphics::Camera> camera) { 
			assert(camera != nullptr);
			this->camera = camera; 
		}

		void startDrawing(std::shared_ptr<Material> material);

		void stopDrawing() {
			material = nullptr;
		}

		virtual void draw(const VertexArray& vertexArray) = 0;
		virtual void clear() const = 0;
	};
}