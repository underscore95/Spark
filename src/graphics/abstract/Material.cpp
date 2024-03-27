#include "Material.h"
#include "Material.h"
#include "Material.h"

void Spark::Graphics::Material::setActiveTextureUniform()
{
	shaders->setUniformSampler2D("Sp_ActiveTexture", activeTextureSlot);
}

void Spark::Graphics::Material::withTexture(std::shared_ptr<Texture> texture, TextureSlot slot)
{
	assertValidTextureSlot(slot);
	if (textures.empty()) {
		activeTextureSlot = slot;
	}
	textures[slot] = texture;
}

void Spark::Graphics::Material::setActiveTexture(Texture& texture)
{
	setActiveTexture(texture.getTextureSlot());
}

void Spark::Graphics::Material::setActiveTexture(const TextureSlot slot)
{
	assertValidTextureSlot(slot);
	activeTextureSlot = slot;
	if (isBound) {
		setActiveTextureUniform();
	}
}

const Spark::Graphics::TextureSlot Spark::Graphics::Material::getActiveTexture() const
{
	return activeTextureSlot;
}

void Spark::Graphics::Material::bind()
{
	isBound = true;

	shaders->bind();

	for (TextureSlot slot = FIRST_TEXTURE_SLOT; slot <= LAST_TEXTURE_SLOT; ++slot) {
		std::stringstream ss;
		ss << "Sp_Texture_" << slot;

		auto it = textures.find(slot);
		if (it == textures.end()) {
			shaders->setUniformSampler2D(ss.str(), NO_TEXTURE_SLOT);
		}
		else {
			auto boundTex = it->second;
			boundTex->bind(slot);
			shaders->setUniformSampler2D(ss.str(), slot);
		}
	}
	for (auto& boundTex : textures) {
		if (boundTex.second == nullptr) continue;
	}

	setActiveTextureUniform();
}

void Spark::Graphics::Material::unbind()
{
	isBound = false;

	for (auto& boundTex : textures) {
		if (boundTex.second == nullptr) continue;
		SparkInternal::Graphics::Textures::unbindTexture(boundTex.second.get());
	}

	shaders->unbind();
}

Spark::Graphics::ShaderProgram& Spark::Graphics::Material::getShaders()
{
	return *shaders;
}
