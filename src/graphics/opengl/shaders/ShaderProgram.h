#pragma once

#include "graphics/abstract/shaders/ShaderProgram.h"

namespace Spark::Graphics::GL {
	class ShaderProgram : public Spark::Graphics::ShaderProgram {
	private:
		const int getUniformLocation(const std::string& variableName) override;
	public:
		ShaderProgram(const std::vector<Shader>& shaders);
		~ShaderProgram();

		void bind() const override;
		void unbind() const override;

		void setUniform2f(const std::string name, float v0, float v1) override;
		void setUniform1i(const std::string name, int i0) override;
		void setUniformSampler2D(const std::string name, Spark::Graphics::Texture& texture) override;
		void setUniformSampler2D(const std::string name, const Spark::Graphics::TextureSlot textureSlot) override;
		void setUniformMat4f(const std::string name, const glm::mat4& m0) override;
	};
}