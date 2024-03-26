#include "Material.h"

void Spark::Graphics::Material::withTexture(std::shared_ptr<Texture> texture, TextureSlot slot)
{
	assertValidTextureSlot(slot);
	textures[slot] = texture;
}

void Spark::Graphics::Material::bind()
{
	shaders->bind();

	for (auto& boundTex : textures) {
		if (boundTex.second == nullptr) continue;
		boundTex.second->bind(boundTex.first);

		std::stringstream ss;
		ss << "Sp_Texture_" << boundTex.first;
		shaders->setUniformSampler2D(ss.str(), *boundTex.second);
	}
}

void Spark::Graphics::Material::unbind()
{
	shaders->unbind();

	for (auto& boundTex : textures) {
		if (boundTex.second == nullptr) continue;
		SparkInternal::Graphics::Textures::unbindTexture(boundTex.second.get());
	}
}

Spark::Graphics::ShaderProgram& Spark::Graphics::Material::getShaders()
{
	return *shaders;
}
