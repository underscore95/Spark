#pragma once

#include "macros.h"
#include <glm/glm.hpp>

namespace Spark::Graphics {
	typedef unsigned int TextureSlot;
	inline constexpr TextureSlot DEFAULT_TEXTURE_SLOT = 0;

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

		/*
		* Binds the texture.
		*
		* \param slot The texture slot to use.
		*/
		virtual void bind(TextureSlot slot = DEFAULT_TEXTURE_SLOT) const = 0;
		virtual void unbind() const = 0;

		const unsigned int getRendererId() const { return rendererId; }
	};
}