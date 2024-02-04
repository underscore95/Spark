#pragma once

#include <GL/glew.h>
#include <cassert>
#include <spdlog/spdlog.h>

namespace GL {
	class TypeConverter {
	public:
		template<typename T>
		static const GLenum getGLType() {
			assert(false);
			spdlog::error("Cannot get GL type");
			return 0;
		}

		template<>
		static const GLenum getGLType<float>() {
			return GL_FLOAT;
		}
	};
}
