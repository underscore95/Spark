#pragma once

#include "pch.h"

namespace Spark::Graphics {
	class Shader {
	protected:
		std::string source;
		std::string filePath;
		unsigned int rendererId;

		/*
		* Read the contents of file at filePath into the source string.
		* Injects sourceToInject at a suitable location for this shader.
		* 
		* By default, source is considered to be GLSL and thus is injected after #version line.
		*/
		virtual	void read(const std::string& sourceToInject);
	public:
		Shader(const std::string& filePath);

		const unsigned int getRendererId() const;
	};
}