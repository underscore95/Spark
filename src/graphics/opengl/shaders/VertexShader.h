#include "graphics/abstract/shaders/Shader.h"

#include <GL/glew.h>

namespace Spark::Graphics::GL {
	class VertexShader : public Spark::Graphics::Shader {
	private:

	public:
		VertexShader(const std::string& filePath);
	};
}