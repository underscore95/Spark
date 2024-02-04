#include "MVP.h"

void GL::MVP::setModel(const glm::mat4& matrix)
{
	// Since projection and view matrices are the same, we can save on a matrix multiplication
	model = matrix;
	pvm = pv * model;
}

void GL::MVP::setView(const glm::mat4& matrix)
{
	view = matrix;
	pv = proj * view;
	pvm = pv * model;
}

void GL::MVP::setProj(const glm::mat4& matrix)
{
	proj = matrix;
	pv = proj * view;
	pvm = pv * model;
}

const glm::mat4& GL::MVP::getMVP() const
{
	return pvm;
}

const glm::mat4& GL::MVP::getModel() const
{
	return model;
}

const glm::mat4& GL::MVP::getView() const
{
	return view;
}

const glm::mat4& GL::MVP::getProj() const
{
	return proj;
}
