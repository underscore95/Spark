#pragma once

#include "macros.h"
#include <glm/glm.hpp>
#include "pch.h"

namespace Spark::Graphics {
	typedef short TextureSlot;
	inline constexpr TextureSlot DEFAULT_TEXTURE_SLOT = 0;
	inline constexpr TextureSlot NO_TEXTURE_SLOT = -1;

	class Texture;
}

namespace SparkInternal::Graphics::Textures {

	Spark::Graphics::TextureSlot getBoundSlot(Spark::Graphics::Texture* texture);
	void unbindTexture(Spark::Graphics::Texture* texture);
	void updateBoundTexture(Spark::Graphics::Texture* texture, Spark::Graphics::TextureSlot slot);
}

namespace Spark::Graphics{
	class Texture {
	protected:
		unsigned int rendererId;
		std::string filePath;
		glm::ivec2 size{ 0,0 };
		int bytesPerPixel{ 0 };
	public:
		DELETE_COPY_MOVE_CONSTRUCTORS(Texture);

		/*
		* Load the file as a texture, ready to be bound.
		*
		* \param filePath The file path.
		*/
		Texture(const std::string& filePath) : filePath{ filePath }, rendererId{ 0 } {}
		~Texture() { SparkInternal::Graphics::Textures::unbindTexture(this); }

		/*
		* Binds the texture. This should update getTextureSlot().
		*
		* \param slot The texture slot to use.
		*/
		virtual void bind(TextureSlot slot = DEFAULT_TEXTURE_SLOT) = 0;

		/*
		* Unbinds the texture. This should update getTextureSlot().
		*/
		virtual void unbind() = 0;

		const unsigned int getRendererId() const { return rendererId; }

		/*
		* \return The texture slot that this texture is currently bound to, or -1 if the texture is not bound
		*/
		const TextureSlot getTextureSlot() { return SparkInternal::Graphics::Textures::getBoundSlot(this); }
	};
}