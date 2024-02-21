#include "graphics/abstract/shaders/Shader.h"

#include <GL/glew.h>

namespace Spark::Graphics::GL {
	class FragmentShader : public Spark::Graphics::Shader {
	private:

	public:
		FragmentShader(const std::string& filePath);
	};
}