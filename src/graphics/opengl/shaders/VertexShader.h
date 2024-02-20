#include "graphics/abstract/shaders/Shader.h"

namespace Spark::Graphics::GL {
	class VertexShader : public Spark::Graphics::Shader {
	private:
		void compile() override;
	public:
		VertexShader(const std::string& filePath);
	};
}