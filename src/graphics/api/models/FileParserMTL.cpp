#include "FileParserMTL.h"
#include "logging/Logger.h"
#include "graphics/api/GraphicsFactory.h"
#include "FileParserOBJ.h"

using namespace Spark::Graphics;

std::unique_ptr<Spark::Graphics::Models::MTLFile> Spark::Graphics::Models::parseMtl(const std::string& folder, const std::string& path, OBJProperties& objProperties)
{
	auto& logger = SparkInternal::getLogger();

	auto mtlFile = std::make_unique<MTLFile>();
	std::ifstream file(folder + path);
	if (!file.is_open())
	{
		std::stringstream ss;
		ss << "Failed to open .mtl file: " << (folder + path) << std::endl;
		logger.severe(ss);
		return nullptr;
	}

	std::string line;
	std::string currentMaterial = "";
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "newmtl")
		{
			ss >> currentMaterial;
			mtlFile->materials[currentMaterial] = std::make_unique<Material>(objProperties.shaders);
		}
		else if (token == "map_Kd")
		{
			std::string texturePath;
			ss >> texturePath;
			assert(mtlFile->materials[currentMaterial] != nullptr);
			assert(!objProperties.textureSlots.empty());
			const auto slot = objProperties.textureSlots.back();
			objProperties.textureSlots.pop_back();
			mtlFile->materials[currentMaterial]->withTexture(Spark::Graphics::loadTexture(folder + texturePath), slot);
		}
	}

	logger.info("Loaded .mtl file: " + (folder + path) + "\n");

	return std::move(mtlFile);
}

std::unique_ptr<Spark::Graphics::Models::MTLFile> Spark::Graphics::Models::mergeMTLFiles(std::unique_ptr<MTLFile> a, std::unique_ptr<MTLFile> b)
{
	for (auto& [name, material] : b->materials)
	{
		a->materials[name] = material;
	}
	return std::move(a);
}
