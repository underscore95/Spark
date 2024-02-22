#include "Texture.h"

namespace SparkInternal::Graphics::Textures {
	std::unordered_map<Spark::Graphics::TextureSlot, Spark::Graphics::Texture*> boundTextures;
	std::unordered_map<Spark::Graphics::Texture*, Spark::Graphics::TextureSlot> textureSlots;

	void updateBoundTexture(Spark::Graphics::Texture* texture, Spark::Graphics::TextureSlot slot) {
		auto currentlyBoundTexture = boundTextures[slot];
		unbindTexture(currentlyBoundTexture);
		unbindTexture(texture);
		boundTextures[slot] = texture;
		textureSlots[texture] = slot;
	}

	void unbindTexture(Spark::Graphics::Texture* texture) {
		if (texture == nullptr) return;
		auto it = textureSlots.find(texture);
		if (it == textureSlots.end()) return; // Already not bound

		auto slot = it->second;
		boundTextures.erase(slot);
		textureSlots.erase(texture);
	}

	Spark::Graphics::TextureSlot getBoundSlot(Spark::Graphics::Texture* texture) {
		auto it = textureSlots.find(texture);
		if (it == textureSlots.end()) return Spark::Graphics::NO_TEXTURE_SLOT;
		return it->second;
	}
}