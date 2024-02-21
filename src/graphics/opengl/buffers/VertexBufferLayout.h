#include "graphics/abstract/buffers/VertexBufferLayout.h"

namespace Spark::Graphics::GL {
	class VertexBufferLayout : public Spark::Graphics::VertexBufferLayout {
	public:
		void pushFloat(unsigned int count) override;
	};
}