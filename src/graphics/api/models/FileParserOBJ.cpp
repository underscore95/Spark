#include "FileParserOBJ.h"
#include "logging/Logger.h"
#include "graphics/api/GraphicsFactory.h"
#include "Utils/WeakVector.h"

using namespace Spark::Graphics;
using namespace SparkInternal::Utils;

void pushVec3(std::stringstream& ss, std::vector<glm::vec3>& vectors)
{
	float x, y, z;
	ss >> x;
	ss >> y;
	ss >> z;
	vectors.emplace_back(x, y, z);
}

void pushVec2(std::stringstream& ss, std::vector<glm::vec2>& vectors)
{
	float x, y;
	ss >> x;
	ss >> y;
	vectors.emplace_back(x, y);
}

void pushVertex(const std::string& token, WeakVector<float>& vertexData, const std::vector<glm::vec3>& verts, const std::vector<glm::vec3>& norms, const std::vector<glm::vec2>& texs)
{
	std::stringstream ss;
	ss << token;
	int v, t, n;
	ss >> v;
	ss.ignore(std::numeric_limits<std::streamsize>::max(), '/');
	ss >> t;
	ss.ignore(std::numeric_limits<std::streamsize>::max(), '/');
	ss >> n;

	vertexData.push_back(verts[v - 1].x);
	vertexData.push_back(verts[v - 1].y);
	vertexData.push_back(verts[v - 1].z);

	vertexData.push_back(norms[n - 1].x);
	vertexData.push_back(norms[n - 1].y);
	vertexData.push_back(norms[n - 1].z);

	vertexData.push_back(texs[t - 1].x);
	vertexData.push_back(texs[t - 1].y);
}

void pushFace(std::stringstream& ss, WeakVector<float>& vertexData, const std::vector<glm::vec3>& verts, const std::vector<glm::vec3>& norms, const std::vector<glm::vec2>& texs)
{
	std::string token;
	for (int i = 0; i < 3; ++i)
	{
		ss >> token;
		pushVertex(token, vertexData, verts, norms, texs);
	}
}

std::shared_ptr<VertexBufferLayout> createLayout() {
	auto layout = Spark::Graphics::createVertexBufferLayout();
	layout->pushFloat(3);
	layout->pushFloat(3);
	layout->pushFloat(2);
	return layout;
}

static std::shared_ptr<VertexBufferLayout> vertexBufferLayout = createLayout();

std::unique_ptr<Spark::Graphics::Model> Spark::Graphics::Models::parseObj(const std::string& path, OBJProperties& objProperties)
{
	auto model = std::make_unique<Model>();

	auto& logger = SparkInternal::getLogger();

	auto mtllib = std::make_unique<Spark::Graphics::Models::MTLFile>();

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::stringstream ss;
		ss << "Failed to open .obj file: " << path << std::endl;
		logger.severe(ss);
		return nullptr;
	}

	std::filesystem::path objPath(path);
	std::string folder = objPath.parent_path().string() + "/";

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> texs;

	WeakVector<float> vertexData;
	std::vector<WeakVector<unsigned int>> indexBuffers;
	std::vector<std::shared_ptr<Material>> materials;
	unsigned int i = 0;

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string token;
		ss >> token;

		if (token == "mtllib") {
			std::string path;
			ss >> path;
			auto newMtl = parseMtl(folder, path, objProperties);
			assert(newMtl != nullptr);
			mtllib = mergeMTLFiles(std::move(mtllib), std::move(newMtl)); // Merge all the materials together
		}
		else if (token == "v") {
			pushVec3(ss, verts); // Vertex position
		}
		else if (token == "vn") {
			pushVec3(ss, norms); // Vertex normal
		}
		else if (token == "vt") {
			pushVec2(ss, texs); // UV coordinate
		}
		else if (token == "f") {
			pushFace(ss, vertexData, verts, norms, texs); // Triangle face
			// Add index for each vertex in the face
			for (int j = 0; j < 3; ++j) {
				indexBuffers.back().push_back(i);
				++i;
			}
		}
		else if (token == "usemtl") {
			std::string material;
			ss >> material;
			// Start a new model segment
			materials.push_back(mtllib->materials[material]);
			indexBuffers.push_back(WeakVector<unsigned int>());
#ifndef NDEBUG
			if (materials.back() == nullptr) {
				logger.severe("Material not found: " + material + "\n");
			}
#endif
		}
	}

	// Finished parsing, now we need to build the buffer objects
	// We'll build once massive vertex buffer and reuse it for each segment
	vertexData.shrink_to_fit();
	std::shared_ptr<VertexBuffer> vertexBuffer = Spark::Graphics::createVertexBuffer(sizeof(float) * vertexData.get_size(), vertexData.get_data());
	assert(indexBuffers.size() == materials.size());
	assert(!materials.empty());

	for (size_t i = 0; i < indexBuffers.size(); ++i) {
		// Get the first index buffer and material
		indexBuffers[i].shrink_to_fit();
		std::shared_ptr<IndexBuffer> indexBuffer = Spark::Graphics::createIndexBuffer(sizeof(unsigned int) * indexBuffers[i].get_size(), indexBuffers[i].get_size(), indexBuffers[i].get_data());

		std::shared_ptr<Material> material = materials[i];

		// Now we need to make a model segment
		std::shared_ptr<VertexArray> va = Spark::Graphics::createVertexArray(indexBuffer, vertexBuffer, vertexBufferLayout);

		ModelSegment segment(va, material);
		model->pushSegment(segment);
	}

	// Finished!
#ifndef NDEBUG
	if (!model->hasSegments()) {
		logger.warning("Model " + path + " has no segments.\n");
	}
#endif

	constexpr const float floatsPerFace = (3 + 3 + 2) * 3;
	logger.info("Loaded .obj file: " + path + " with " + std::to_string(vertexData.get_size() / floatsPerFace) + " faces.\n");

	return std::move(model);
}
