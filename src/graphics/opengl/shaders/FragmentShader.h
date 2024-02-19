#include "graphics/abstract/shaders/Shader.h"

namespace Spark::Graphics::GL {
	class FragmentShader : public Spark::Graphics::Shader {
	private:
		void compile() override;
	};
}