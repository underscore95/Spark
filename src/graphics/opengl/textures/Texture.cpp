#include "Texture.h"

#include <GL/glew.h>
#include <stb_image.h>
#include "logging/Logger.h"
#include "logging/Logging.h"

Spark::Graphics::GL::Texture::Texture(const std::string& filePath) : Spark::Graphics::Texture(filePath) {
	unsigned char* localBuffer = stbi_load(filePath.c_str(), &size.x, &size.y, &bytesPerPixel, 4);

	glGenTextures(1, &rendererId);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	unbind();

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}

	auto& logger = SparkInternal::getLogger();
	logger.debug("Loaded texture " + filePath + " successfully!");
}

Spark::Graphics::GL::Texture::~Texture() {
	glDeleteTextures(1, &rendererId);
}

void Spark::Graphics::GL::Texture::bind(Spark::Graphics::TextureSlot slot)
{
	SparkInternal::Graphics::Textures::updateBoundTexture(this, slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, rendererId);
}

void Spark::Graphics::GL::Texture::unbind() {
	SparkInternal::Graphics::Textures::unbindTexture(this);
	glBindTexture(GL_TEXTURE_2D, rendererId);
}