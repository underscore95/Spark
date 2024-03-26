#include "FragmentShader.h"
#include "ShaderUtils.h"

const std::string INJECT_SOURCE = R"(
        uniform sampler2D Sp_Texture_0;
		uniform sampler2D Sp_Texture_1;
		uniform sampler2D Sp_Texture_2;
		uniform sampler2D Sp_Texture_3;
		uniform sampler2D Sp_Texture_4;
		uniform sampler2D Sp_Texture_5;
		uniform sampler2D Sp_Texture_6;
		uniform sampler2D Sp_Texture_7;
		uniform sampler2D Sp_Texture_8;
		uniform sampler2D Sp_Texture_9;
		uniform sampler2D Sp_Texture_10;
		uniform sampler2D Sp_Texture_11;
		uniform sampler2D Sp_Texture_12;
		uniform sampler2D Sp_Texture_13;
		uniform sampler2D Sp_Texture_14;
		uniform sampler2D Sp_Texture_15;
		uniform sampler2D Sp_Texture_16;
		uniform sampler2D Sp_Texture_17;
		uniform sampler2D Sp_Texture_18;
		uniform sampler2D Sp_Texture_19;
		uniform sampler2D Sp_Texture_20;
		uniform sampler2D Sp_Texture_21;
		uniform sampler2D Sp_Texture_22;
		uniform sampler2D Sp_Texture_23;
		uniform sampler2D Sp_Texture_24;
		uniform sampler2D Sp_Texture_25;
		uniform sampler2D Sp_Texture_26;
		uniform sampler2D Sp_Texture_27;
		uniform sampler2D Sp_Texture_28;
		uniform sampler2D Sp_Texture_29;
		uniform sampler2D Sp_Texture_30;
		uniform sampler2D Sp_Texture_31;
    )";

Spark::Graphics::GL::FragmentShader::FragmentShader(const std::string& filePath) : Spark::Graphics::Shader(filePath)
{
	read(INJECT_SOURCE);
	compileShader(GL_FRAGMENT_SHADER, source, filePath, rendererId);

#ifndef NDEBUG
	if (rendererId == 0) {
		auto& logger = SparkInternal::getLogger();
		logger.warning("OpenGL FragmentShader has id 0");
	}
#endif
}
