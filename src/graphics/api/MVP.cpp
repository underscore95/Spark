#include "MVP.h"

void Spark::Graphics::MVP::setModel(const glm::mat4& matrix)
{
	// Since projection and view matrices are unchanged, we can save on a matrix multiplication
	model = matrix;
	pvm = pv * model;
}

void Spark::Graphics::MVP::setView(const glm::mat4& matrix)
{
	view = matrix;
	pv = proj * view;
	pvm = pv * model;
}

void Spark::Graphics::MVP::setProj(const glm::mat4& matrix)
{
	proj = matrix;
	pv = proj * view;
	pvm = pv * model;
}

const glm::mat4& Spark::Graphics::MVP::getMVP() const
{
	return pvm;
}

const glm::mat4& Spark::Graphics::MVP::getModel() const
{
	return model;
}

const glm::mat4& Spark::Graphics::MVP::getView() const
{
	return view;
}

const glm::mat4& Spark::Graphics::MVP::getProj() const
{
	return proj;
}
