#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Spark::Graphics {
	/*
	* Holds the Model View Projection matrix
	* This class is implemented using column major matrices since that is how OpenGL works (proj * view * model). May be changed in the future.
	* By default, all matrices are identity matrices
	*/
	class MVP {
	private:
		glm::mat4 model{ glm::identity<glm::mat4>() };
		glm::mat4 view{ glm::identity<glm::mat4>() };
		glm::mat4 proj{ glm::identity<glm::mat4>() };

		glm::mat4 pv{ glm::identity<glm::mat4>() };
		glm::mat4 pvm{ glm::identity<glm::mat4>() };
	public:
		/*
		* Set the model matrix.
		* This method updates the model matrix and recalculates the MVP matrix.
		*/
		void setModel(const glm::mat4& matrix);

		/*
		* Set the view matrix.
		* This method updates the view matrix and recalculates the MVP matrix.
		*/
		void setView(const glm::mat4& matrix);

		/*
		* Set the projection matrix.
		* This method updates the projection matrix and recalculates the MVP matrix.
		*/
		void setProj(const glm::mat4& matrix);

		/*
		* Get the model view projection matrix.
		* Returns the current model view projection matrix.
		*/
		const glm::mat4& getMVP() const;

		/*
		* Get the model matrix.
		* Returns the current model matrix.
		*/
		const glm::mat4& getModel() const;

		/*
		* Get the view matrix.
		* Returns the current view matrix.
		*/
		const glm::mat4& getView() const;

		/*
		* Get the projection matrix.
		* Returns the current projection matrix.
		*/
		const glm::mat4& getProj() const;

	};
}