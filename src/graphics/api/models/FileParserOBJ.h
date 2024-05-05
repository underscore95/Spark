#pragma once

#include "FileParserMTL.h"
#include "graphics/abstract/models/Model.h"

namespace Spark::Graphics::Models {
	struct OBJProperties {
		std::shared_ptr<ShaderProgram> shaders; // Shaders to use
		std::vector<TextureSlot> textureSlots; // Texture slots that can be used, this vector will be mutated (removes used slots)
	};

	/*
	* See https://en.wikipedia.org/wiki/Wavefront_.obj_file for more information
	* 
	* Parse an obj file. Supports only the following features:
	* mtllib, usemtl, v, vt, vn, f
	* 
	* Does not support multiple objects in the same file.
	* Faces must be triangles. Faces must be at the end of the file.
	* Stringstream is used for parsing, so spaces in file names, etc, will not work.
	* 
	* See FileParserMTL.h for supported mtl features
	* 
	* @param path Path to the obj file
	* @param objProperties Properties to use when parsing the obj file
	* 
	* @return A model object
	*/
	[[nodiscard]] std::unique_ptr<Spark::Graphics::Model> parseObj(const std::string& path, OBJProperties& objProperties);
}