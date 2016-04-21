#include "Point.h"

tower_defense::Point::Point() : Point(0.0, 0.0) {
}

tower_defense::Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

tower_defense::Point::Point(const Point &p) : Point(p.x, p.y) {
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


tower_defense::Point tower_defense::Point::operator-(const Point &p) const {
	return Point(x - p.x, y - p.y);
}
tower_defense::Point tower_defense::Point::operator+(const Point &p) const {
	return Point(x + p.x, y + p.y);
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