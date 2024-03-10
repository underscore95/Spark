#include "graphics/abstract/shaders/Shader.h"

#include <GL/glew.h>

namespace Spark::Graphics::GL {
	class VertexShader : public Spark::Graphics::Shader {
	private:
		void injectShaderCode();

	public:
		VertexShader(const std::string& filePath);
	};
}