#pragma once

#include "shaders/ShaderProgram.h"
#include "textures/Texture.h"

namespace Spark::Graphics {
	class Material {
	private:
		std::shared_ptr<ShaderProgram> shaders;
		std::unordered_map<TextureSlot, std::shared_ptr<Texture>> textures;
	public:
		Material(std::shared_ptr<ShaderProgram> shaders) : shaders{ shaders } { assert(shaders != nullptr); }

		void withTexture(std::shared_ptr<Texture> texture, TextureSlot slot);

		void bind();
		void unbind();

		ShaderProgram& getShaders();
	};
}