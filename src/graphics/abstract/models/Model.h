#pragma once

#include "graphics/abstract/buffers/VertexArray.h"
#include "graphics/abstract/Material.h"

namespace Spark::Graphics {
	struct ModelSegment {
	public:
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<Material> material;

		ModelSegment(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
			: vertexArray(vertexArray), material(material) {}
	};

	class Model {
	private:
		std::vector<ModelSegment> segments;
	public:
		inline void pushSegment(const ModelSegment& segment) { segments.push_back(segment); }
		[[nodiscard]] inline const std::vector<ModelSegment>& getSegments() const { return segments; }
		[[nodiscard]] inline const bool hasSegments() const { return !segments.empty(); }
	};
}