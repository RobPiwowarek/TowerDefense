#include "Turret.h"


tower_defense::Turret::Turret(const int size, const int turretClass, const double rotationSpeed, const int level,
                              const Weapon &wBase, int armor)
        : Entity(Point(), 0, size, turretClass) {
    this->weapon = new Weapon(wBase, this);
    this->rotationSpeed = rotationSpeed;
    this->level = level;
    this->armor = armor;
}

tower_defense::Turret::Turret(const Turret &base, const Point &location)
        : Entity(base) {
    this->weapon = new Weapon(*base.weapon, this);
    this->location = location;
    this->level = base.level;
    this->rotationSpeed = base.rotationSpeed;
    this->armor = base.armor;
}

int tower_defense::Turret::getArmor() const { return this->armor; }

void tower_defense::Turret::setArmor(int armor) { this->armor = armor; }

int tower_defense::Turret::getCurrentHealth() const { return this->currentHealth; }

int tower_defense::Turret::getMaxHealth() const { return this->maxHealth; }

bool tower_defense::Turret::receiveDamage(const int damage, Grid &g) {
    if (this->currentHealth <= 0) return false;
    else {
        this->currentHealth -= damage;
    }

    if (this->currentHealth <= 0) this->destroy(g);

    return true;
}

//TODO: implement
void tower_defense::Turret::destroy(Grid &g) {
    g.getElement(this->location)->setTurret(nullptr);
	this->toRemove = true;
}

void tower_defense::Turret::setCurrentHealth(int currentHealth) {
    if (currentHealth >= this->maxHealth) {
        this->currentHealth = this->maxHealth;
    }
    else
        this->currentHealth = currentHealth;
}

const double PI = 3.1415;
double normalizeAngle(double angle) {
	while (angle <= -PI) angle += 2 * PI;
	while (angle > PI) angle -= 2 * PI;
	return angle;
}

double angleDiff(double from, double to) {
	return normalizeAngle(from - to);
}

#include <iostream>

bool tower_defense::Turret::shouldBeRemoved() const{
	return this->toRemove;
}

void tower_defense::Turret::setToRemove(const bool b){
	this->toRemove = b;
}

bool tower_defense::Turret::refresh(Map* map) {
    // assuming first enemy is the closest in angle
    // TODO: change to one closest to the item
	if (!this->toRemove){

		Minion* target = nullptr;
		double angleD;
		double nAngleD;

		std::set<GridElement*> fireRange = map->getGrid().getElementsInRadius(this->location, this->weapon->getRange());

		for (GridElement* g : fireRange) {
			for (Minion* m : g->getMinions()) {
				if (this->location.getSquareDistance(m->getLocation()) <= this->weapon->getRange() * this->weapon->getRange())
					if (target == nullptr) {
						target = m;
						angleD = angleDiff(this->angle,
							-atan2(this->location.getX() - m->getLocation().getX(),
							this->location.getY() - m->getLocation().getY()));
					}
					else if (abs(nAngleD = angleDiff(this->angle,
						-atan2(this->location.getX() - m->getLocation().getX(),
						this->location.getY() - m->getLocation().getY()))) < abs(angleD)) {
						target = m;
						angleD = nAngleD;
					}
			}
		}
		//std::cout << angle << "\t" << angleD << std::endl;
		if (target != nullptr) {
			if (abs(angleD) < this->rotationSpeed)	this->angle -= angleD;
			else if (angleD > 0)					this->angle -= this->rotationSpeed;
			else									this->angle += this->rotationSpeed;

			this->angle = normalizeAngle(this->angle);

			this->weapon->refresh(abs(angleD) < this->rotationSpeed, map);
		}
		else this->weapon->refresh(false, map);

		return true;

	}
}

tower_defense::Turret::~Turret() {
    delete this->weapon;
}

double tower_defense::Turret::getRotationSpeed() const {
    return this->rotationSpeed;
}

void tower_defense::Turret::setRotationSpeed(const double d) {
    this->rotationSpeed = d;
    if (this->rotationSpeed < 0)
        this->rotationSpeed *= -1;
}


int tower_defense::Turret::getLevel() const {
    return this->level;
}

void tower_defense::Turret::setLevel(int lvl) {
    this->level = lvl;
}

tower_defense::Weapon &tower_defense::Turret::getWeapon() {
    return *this->weapon;
}