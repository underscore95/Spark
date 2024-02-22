#include "MVP.h"

void Spark::Utils::MVP::setModel(const glm::mat4& matrix)
{
	// Since projection and view matrices are unchanged, we can save on a matrix multiplication
	model = matrix;
	pvm = pv * model;
}

void Spark::Utils::MVP::setView(const glm::mat4& matrix)
{
	view = matrix;
	pv = proj * view;
	pvm = pv * model;
}

void Spark::Utils::MVP::setProj(const glm::mat4& matrix)
{
	proj = matrix;
	pv = proj * view;
	pvm = pv * model;
}

const glm::mat4& Spark::Utils::MVP::getMVP() const
{
	return pvm;
}

const glm::mat4& Spark::Utils::MVP::getModel() const
{
	return model;
}

const glm::mat4& Spark::Utils::MVP::getView() const
{
	return view;
}

const glm::mat4& Spark::Utils::MVP::getProj() const
{
	return proj;
}
