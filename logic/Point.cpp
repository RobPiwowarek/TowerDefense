#include "Point.h"
#include <cmath>
#include <iostream>

tower_defense::Point::Point() : Point(0.0, 0.0) {
}

tower_defense::Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

tower_defense::Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

tower_defense::Point::Point(const Point &p) : Point(p.x, p.y) {
}

std::string tower_defense::Point::toString() const {
	std::string info = std::string("(") + std::to_string(this->x) + ',' + std::to_string(this->y) + ")";

	return info;
}

void tower_defense::Point::print() const {
	std::cout << this->toString() << std::endl;
}

double tower_defense::Point::getX() const {
    return this->x;
}

double tower_defense::Point::getY() const {
    return this->y;
}

void tower_defense::Point::setX(double x) {
    this->x = x;
}

void tower_defense::Point::setY(double y) {
    this->y = y;
}

void tower_defense::Point::setPoint(const Point &p) {
    this->x = p.getX();
    this->y = p.getY();
}

inline double square(double x) { return x * x; }

double tower_defense::Point::getSquareDistance(const tower_defense::Point &p) const {
	return square(this->x - p.getX()) + square(this->y - p.getY());
}

double tower_defense::Point::getSqDistFromSegment(const tower_defense::Point& A, const tower_defense::Point& B) const {
	//lets say that the segment is a part of line k, with given equation: k = (vec)A + (vec)AB * t
	//then lets count t0 that is t with minimal distance from this point

	tower_defense::Point AB = B - A;
	double t0 = (this->x * AB.x + this->y * AB.y - A.x * AB.x - A.y * AB.y) / (AB.x * AB.x + AB.y * AB.y);

	// if t0 is between 0 and 1 than it is closer to the segment than points A and B
	// else if t0 is lower than 0 it is closer to point A
	// else id it is greater than 1 it is closer to point B

	if (t0 < 0) return getSquareDistance(A);
	if (t0 > 1) return getSquareDistance(B);
	else return square(A.x + AB.x * t0 - this->x) + square(A.y + AB.y * t0 - this->y);
}

tower_defense::Point tower_defense::Point::operator-(const Point &p) const {
	return Point(x - p.x, y - p.y);
}
tower_defense::Point tower_defense::Point::operator+(const Point &p) const {
	return Point(x + p.x, y + p.y);
}

tower_defense::Point tower_defense::Point::operator+(const double val) const{
	return Point(this->x + val, this->y + val);
}

tower_defense::Point tower_defense::Point::operator-(const double val) const{
	return Point(this->x - val, this->y - val);
}

tower_defense::Point& tower_defense::Point::operator+=(const Point &p) {
	this->x += p.x;
	this->y += p.y;
	return *this;
}
tower_defense::Point& tower_defense::Point::operator-=(const Point &p) {
	this->x -= p.x;
	this->y -= p.y;
	return *this;
}

tower_defense::Point tower_defense::Point::operator*(double i) const {
	return Point(x * i, y * i);
}
tower_defense::Point tower_defense::Point::operator/(double i) const {
	return Point(x / i, y / i);
}
tower_defense::Point& tower_defense::Point::operator*=(double i) {
	this->x *= i;
	this->y *= i;
	return *this;
}
tower_defense::Point& tower_defense::Point::operator/=(double i) {
	this->x /= i;
	this->y /= i;
	return *this;
}