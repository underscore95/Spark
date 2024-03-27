#pragma once

#include "shaders/ShaderProgram.h"
#include "textures/Texture.h"

namespace Spark::Graphics {
	class Material {
	private:
		std::shared_ptr<ShaderProgram> shaders;
		std::unordered_map<TextureSlot, std::shared_ptr<Texture>> textures;

		TextureSlot activeTextureSlot = NO_TEXTURE_SLOT;

		bool isBound = false;
		void setActiveTextureUniform();
	public:
		Material(std::shared_ptr<ShaderProgram> shaders) : shaders{ shaders } { assert(shaders != nullptr); }

		/*
		* Bind a texture to this material. If this is the first texture bound, the active texture will be set to this.
		*/
		void withTexture(std::shared_ptr<Texture> texture, TextureSlot slot);

		void setActiveTexture(Texture& texture);
		void setActiveTexture(const TextureSlot slot);
		const TextureSlot getActiveTexture() const;

		/*
		* Bind the material, note that it must be unbound before another material is bound.
		*/
		void bind();
		/*
		* Unbind the material.
		*/
		void unbind();

		ShaderProgram& getShaders();
	};
}