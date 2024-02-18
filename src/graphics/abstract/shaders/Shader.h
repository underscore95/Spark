#pragma once

#include "pch.h"

namespace Spark::Graphics {
	class Shader {
	private:
		std::string source;
		std::string filePath;
		unsigned int rendererId;

		void read();
		virtual void compile() = 0;

	public:
		Shader(const std::string& filePath);

		const unsigned int getRendererId() const;
	};
}