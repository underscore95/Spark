#pragma once

namespace Spark::Graphics {
	struct VertexBufferLayoutElement {
		unsigned int index;
		unsigned int count;
		unsigned int type;
		bool normalized;
		unsigned int size;
	};

	/*
	* Describes how the vertex buffer data is layed out.
	* e.g "Hey one vertex consists of 3 floats (position), then 2 more floats (texture coordinates)"
	*/
	class VertexBufferLayout {
	private:
		std::vector<VertexBufferLayoutElement> elements;
		unsigned int stride{ 0 };
	protected:
		void push(unsigned int size, unsigned int count, unsigned int type, bool normalized = false) {
			stride += size * count;		
			elements.emplace_back(elements.size(), count, type, normalized, size);
		}
	public:
		/*
		* \param count Number of floats in this element
		*/
		virtual void pushFloat(unsigned int count) = 0;

		/*
		* \return The stride (size of a vertex) in bytes.
		*/
		const unsigned int& getStride() const {
			return stride;
		}

		const std::vector<VertexBufferLayoutElement>& getElements() const {
			return elements;
		}
	};
}