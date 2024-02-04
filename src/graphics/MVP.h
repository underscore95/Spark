#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GL {
	// Holds the MVP matrix
	// This class is implemented using column major matrices since that is how opengl works (proj * view * model)
	// By default, all matrices are identity matrices
	class MVP {
	private:
		glm::mat4 model{ glm::identity<glm::mat4>() };
		glm::mat4 view{ glm::identity<glm::mat4>() };
		glm::mat4 proj{ glm::identity<glm::mat4>() };

		glm::mat4 pv{ glm::identity<glm::mat4>() };
		glm::mat4 pvm{ glm::identity<glm::mat4>() };
	public:
		// Update the model matrix and recalculate the MVP matrix.
		void setModel(const glm::mat4& matrix);
		// Update the view matrix and recalculate the MVP matrix
		void setView(const glm::mat4& matrix);
		// Update the projection matrix and recalculate the MVP matrix
		void setProj(const glm::mat4& matrix);

		// Get the model view projection matrix
		const glm::mat4& getMVP() const;

		// Get the model matrix
		const glm::mat4& getModel() const;
		// Get the view matrix
		const glm::mat4& getView() const;
		// Get the projection matrix
		const glm::mat4& getProj() const;
	};
}