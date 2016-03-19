#include "PathElement.h"
#include <cmath>

tower_defense::PathElement::PathElement(
	const int nInPath, const tower_defense::Point& translation, const tower_defense::Point& x0)
{
	this->nInPath = nInPath;
	this->translation = translation;
	this->x0 = x0;
}

double tower_defense::PathElement::getAngle() const
{
	return atan2(this->translation.getX(), this->translation.getY());
}

int tower_defense::PathElement::getNInPath() const
{
	return this->nInPath;
}

const tower_defense::Point& tower_defense::PathElement::getX0() const
{
	return this->x0;
}

const tower_defense::Point& tower_defense::PathElement::getTranslation() const
{
	return this->translation;
}