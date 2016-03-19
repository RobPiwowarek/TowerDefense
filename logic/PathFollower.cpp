#include "PathFollower.h"

tower_defense::PathFollower::PathFollower(
	const double velocity, const double size, const int objClass)
	: Entity(Point(), 0.0, size, objClass)
{
	this->velocity = velocity;
}

tower_defense::PathFollower::PathFollower(
	const PathFollower& p, const Path* path)
	: Entity(Point(), 0.0, p.size, p.objClass)
{
	this->velocity = p.velocity;
	this->path = path;

	this->curElement = this->path->getFirst();

	if (this->curElement != nullptr)
	{
		this->location = this->curElement->getX0();
		this->angle = this->curElement->getAngle();
	}
}