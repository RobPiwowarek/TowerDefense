#include "Beam.h"
#include <iostream>

#define SQ(X) ((X)*(X))

tower_defense::Beam::Beam(const int damage, const double maxSize, const int fireClass, const bool hitOnlyFirst, const double width)
	: WeaponFire(damage, maxSize, 1, beam, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
	this->width = width;
}

tower_defense::Beam::Beam(const Beam &base, const Point &location, const double angle, const double angleModifier)
	: WeaponFire(base, location, angle, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
	this->width = base.width;
}

bool tower_defense::Beam::isHitOnlyFirst() const {
    return this->hitOnlyFirst;
}

bool tower_defense::Beam::refresh(Grid& g) {
	this->updateEndLocation();

	Minion* closest = nullptr;

	for (tower_defense::GridElement* element : g.getElementsInLine(this->location, this->endLocation, this->width/2)){
		for (tower_defense::Minion* minion : element->getMinions()){
			if (this->checkCollision(minion)){
				if (!hitOnlyFirst)
					minion->takeDamage(this->damage);
				else closest = closest == nullptr ? minion :
					this->location.getSquareDistance(closest->getLocation()) < this->location.getSquareDistance(minion->getLocation()) ?
				closest : minion;
			}
		}
	}

	if (hitOnlyFirst && closest) {
		closest->takeDamage(this->damage);

		double nx, ny;
		if (this->location.getX() == this->endLocation.getX()) {
			nx = this->endLocation.getX();
			ny = sqrt(SQ(closest->getSize() /2) - SQ(nx - closest->getLocation().getX())) + closest->getLocation().getY();
		}
		else { //y = ax + b
			double a = (this->location.getY() - this->endLocation.getY()) / (this->location.getX() - this->endLocation.getX());
			double b = this->location.getY() - a * this->location.getX();

			//(x-Cx)2 + (y-Cy)2 = r2 AND y = ax + b
			//x2 + Cx2 - 2xCx + Cy2 +a2x2 + b2 + 2abx -2bCy - 2axCy - r2 = 0
			//(1 + a2)x2 + (-2Cx + 2ab - 2aCy)x + Cx2 + Cy2 + b2 - 2bCy - r2 = 0
			//Ax + By + C = 0
			double A = 1 + SQ(a);
			double B = -2 * closest->getLocation().getX() + 2 * a * b - 2 * a * closest->getLocation().getY();
			double C = SQ(closest->getLocation().getX()) + SQ(closest->getLocation().getY()) + SQ(b) 
				- 2 * b * closest->getLocation().getY() - SQ(closest->getSize() / 2);
			
			//need only one solution, lets say x = (sqrt(B2 - 4AC) - B) / (2 * A) and y = ax + b
			nx = (sqrt(SQ(B) - 4 * A*C) - B) / (2 * A);
			ny = a * nx + b;
		}

		this->endLocation = { nx, ny };
	}


	//for purpose of displaying:
	this->location = (this->location + this->endLocation) / 2;


	this->size = 2 * sqrt(SQ(this->location.getX() - this->endLocation.getX()) + SQ(this->location.getY() - this->endLocation.getY()));

	this->toRemove = true;
	return false; //TODO
}

std::string tower_defense::Beam::toString() const{
	std::string info = std::string("Beam: Damage: ") + (char)this->damage + " Angle: " + (char)this->angle + " Size: " 
		+ (char)this->size + " LifeTime: " + (char) this->lifeTime + " Width: " + (char) this->width + " HitOnlyFirst: " 
		+ (char)this->hitOnlyFirst + " Location: " + this->location.toString() +" EndLocation: " + this->endLocation.toString();

	return info;
}

void tower_defense::Beam::print() const{
	std::cout << this->toString() << std::endl;
}

double tower_defense::Beam::getWidth() const{
	return this->width;
}

void tower_defense::Beam::updateEndLocation(){
	this->endLocation = this->location + Point { this->size * sin(angle), -this->size * cos(angle)};
}

tower_defense::Point tower_defense::Beam::getEndLocation() const{
	return this->endLocation;
}

void tower_defense::Beam::setWidth(const double width){
	this->width = width;
}

void tower_defense::Beam::setEndLocation(const Point& p){
	this->endLocation = p;
}

void tower_defense::Beam::setEndLocation(const int x, const int y){
	this->endLocation = { x, y };
}

void tower_defense::Beam::setEndLocation(const double x, const double y){
	this->endLocation = { x, y };
}

bool tower_defense::Beam::hits(Minion* m) {
	return false; //TODO
}

bool tower_defense::Beam::checkCollision(tower_defense::Minion * minion){
	double d = minion->getLocation().getSqDistFromSegment(this->location, this->endLocation);

	if (d <= pow(minion->getSize()/2 + this->width/2, 2.0f)) return true;

	return false; //TODO
}