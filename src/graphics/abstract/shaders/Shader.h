#pragma once

#include "pch.h"

namespace Spark::Graphics {
	class Shader {
	protected:
		std::string source;
		std::string filePath;
		unsigned int rendererId;

		void read();

	public:
		Shader(const std::string& filePath);

		const unsigned int getRendererId() const;
	};
}