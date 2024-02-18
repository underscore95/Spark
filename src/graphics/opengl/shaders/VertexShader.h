#include "graphics/abstract/shaders/Shader.h"

namespace Spark::Graphics::GL {
	class VertexShader : public Spark::Graphics::Shader {
	public:
		void compile() override;
	};
}