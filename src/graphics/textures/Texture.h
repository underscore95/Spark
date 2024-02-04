#pragma once

#include <string>
#include <glm/vec2.hpp>

namespace GL {
	class Texture {
	private:
		unsigned int id{ 0 };
		std::string filePath;
		glm::ivec2 size{ 0,0 };
		int bytesPerPixel{ 0 };
	public:
		Texture(const std::string& filePath);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		const glm::vec2& getSize() const { return size; }
		const int getBitsPerPixel() const { return bytesPerPixel; }
};
}