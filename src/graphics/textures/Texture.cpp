#include "Texture.h"
#include <GL/glew.h>
#include <stb_image.h>

GL::Texture::Texture(const std::string& filePath)
	: filePath{ filePath }
{
	unsigned char* localBuffer = stbi_load(filePath.c_str(), &size.x, &size.y, &bytesPerPixel, 4);

	glGenTextures(1, &id);
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
}

GL::Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void GL::Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void GL::Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
