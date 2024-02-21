#pragma once

#include "graphics/abstract/textures/Texture.h"

namespace Spark::Graphics::GL {
	class Texture : public Spark::Graphics::Texture {
	public:
		Texture(const std::string& filePath);
		~Texture();

		void bind(Spark::Graphics::TextureSlot slot = DEFAULT_TEXTURE_SLOT) const override;
		void unbind() const override;
	};
}