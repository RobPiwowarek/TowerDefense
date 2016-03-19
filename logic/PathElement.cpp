#include "PathElement.h"
#include <cmath>

tower_defense::PathElement::PathElement(
        const int nInPath, const tower_defense::Point &translation, const tower_defense::Point &x0) {
    this->nInPath = nInPath;
    this->x1 = x1;
    this->x0 = x0;
}

// TODO: check if i got math right, its preeety late
double tower_defense::PathElement::getSqDistance(const Entity *e) const {
    double A, B; // y = Ax + B
    double d; // distance

    A = (this->getX1().getX() - this->getX0().getX()) / (this->getX1().getY() - this->getX0().getY());
    B = this->getX1().getY() - A * this->getX1().getX();

    d = pow(A * e->getLocation().getX() - e->getLocation().getY() + B, 2.0f) / (A * A + B * B);

    return d;
}

double tower_defense::PathElement::getAngle() const {
    return atan2(this->X1.getX(), this->X1.getY());
}

int tower_defense::PathElement::getNInPath() const {
    return this->nInPath;
}

const tower_defense::Point &tower_defense::PathElement::getX0() const {
    return this->x0;
}

const tower_defense::Point &tower_defense::PathElement::getX1() const {
    return this->x1;
}