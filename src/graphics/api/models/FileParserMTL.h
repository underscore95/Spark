#pragma once

#include "pch.h"
#include "graphics/abstract/Material.h"
#include "graphics/abstract/shaders/ShaderProgram.h"

namespace Spark::Graphics::Models {

	struct OBJProperties;

	struct MTLFile {
		std::unordered_map<std::string, std::shared_ptr<Material>> materials;
	};

	/*
	* Parse a .mtl file and return a Material object.
	* Can only parse very basic files, only understands diffuse texture maps.
	* Stringstream is used for parsing, so spaces in file names, etc, will not work.
	*/
	[[nodiscard]] std::unique_ptr<MTLFile> parseMtl(const std::string& folder, const std::string& path, OBJProperties& objProperties);

	/*
	* Merge two MTLFiles together, the second file will overwrite any materials with the same name.
	* The first file will be modified and returned.
	*/
	[[nodiscard]] std::unique_ptr<MTLFile> mergeMTLFiles(std::unique_ptr<MTLFile> a, std::unique_ptr<MTLFile> b);
}