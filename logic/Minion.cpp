#include "Minion.h"

#define PI 3.1415

// TODO: czemu entity(point(0,0))? Re: w sumie nie ma znaczenia, ale konstruktor wymaga jakiegos
tower_defense::Minion::Minion(
        const double velocity, const double size, const int minionClass,
        const int reward, const int health, const int damage, const TargetPriority priority)
        : Entity(Point(0, 0), 0.0, size, minionClass) {
    this->velocity = velocity;
    this->reward = reward;
    this->health = health;
    this->next = nullptr;
    this->target = priority;
}

tower_defense::Minion::Minion(const Minion &base, const Point &x0)
        : Entity(base) {
    this->velocity = base.velocity;
    this->reward = base.reward;
    this->health = base.health;
    this->location = x0;
    this->next = nullptr;
	this->target = base.target;
}

void tower_defense::Minion::attack(tower_defense::Turret &turret) const{
    int damage = this->damage - turret.getArmor();

    if (damage < 0) return;

    turret.setCurrentHealth(turret.getCurrentHealth() - damage);
}

tower_defense::Item* tower_defense::Minion::getItem() const { return this->item; }

bool tower_defense::Minion::hasItem() const { return this->item != nullptr; }

bool tower_defense::Minion::hasItem(tower_defense::Item* item) const { return this->item != item; }

bool tower_defense::Minion::setItem(tower_defense::Item* item) { 
	
	if (this->item != nullptr) return false;

	this->item = item; 
	return true;
}

bool tower_defense::Minion::takeDamage(const double damage){
	if (this->health <= 0 || this->dead) return false; //check if already dead

	this->health -= damage;

	return true;
}

bool tower_defense::Minion::isDead() const {
    return this->dead;
}

void tower_defense::Minion::death(Game &game) {
    this->dead = true;

    game.getPlayer().setMoney(this->reward);

    game.getMap().removeMinion(this);
}

#include <iostream>

void tower_defense::Minion::chooseDestination(Grid &g, Game &game) {
    GridElement* currentLocation = g.getElement(this->location);
    GridElement* left = currentLocation->getLeftNeighbour(),
		*right = currentLocation->getRightNeighbour(),
		*up = currentLocation->getUpNeighbour(),
		*down = currentLocation->getDownNeighbour();

    this->next = nullptr;

	auto dist = GridElement::getDistToTarget;

	

    if (currentLocation->getDistToTarget() != -1 && (target == Item || currentLocation->getDistToTurret() == -1
		|| (target == Closer &&	(currentLocation->getDistToTarget() <= currentLocation->getDistToTurret())))) { // Go to target

		int dist = currentLocation->getDistToTarget();
		std::cout << "a";
        if (left != nullptr)
			if (!left->hasTurret() && left->getDistToTarget() < dist) {
				this->next = left;
				this->angle = -PI/2;
			}

		if (right != nullptr)
			if (!right->hasTurret() && right->getDistToTarget() < dist) {
				this->next = right;
				this->angle = PI/2;
			}

		if (up != nullptr)
			if (!up->hasTurret() && up->getDistToTarget() < dist) {
				this->next = up;
				this->angle = 0.0;
			}

		if (down != nullptr)
			if (!down->hasTurret() && down->getDistToTarget() < dist) {
				this->next = down;
				this->angle = PI;
			}
		std::cout << "b";
    }

    else if (currentLocation->getDistToTurret() != -1){ // Go to turret
		int dist = currentLocation->getDistToTurret();

		if (left != nullptr)
			if (left->hasTurret() || left->getDistToTurret() < dist) {
				this->next = left;
				this->angle = -PI / 2;
			}

		if (right != nullptr)
			if (right->hasTurret() || right->getDistToTurret() < dist) {
				this->next = right;
				this->angle = PI / 2;
			}

		if (up != nullptr)
			if (up->hasTurret() || up->getDistToTurret() < dist) {
				this->next = up;
				this->angle = 0.0f;
			}

		if (down != nullptr)
			if (down->hasTurret() || down->getDistToTurret() < dist) {
				this->next = down;
				this->angle = PI;
			}
	}
}

void tower_defense::Minion::refresh(Grid &g, Game &game) {
    if (this->health <= 0) {
        this->death(game);
		return;
    }
	if (this->next == nullptr || this->next == g.getElement(this->location))
		this->chooseDestination(g, game);

	if (this->next != nullptr)
		if (this->next->hasTurret())
			this->attack(*this->next->getTurret());

    if (this->target == Item) {
        if (g.getElement(this->location)->hasItem()){
            g.getElement(this->location)->getItem().pickUp(this, g);
        }
    }

    // Update location
    
	this->location.setX(this->location.getX() + this->velocity*sin(this->angle));
	this->location.setY(this->location.getY() - this->velocity*cos(this->angle));

	
	if (g.getElement(this->location) == this->next)
		this->next = nullptr;
}

int tower_defense::Minion::getDamage() const {
    return this->damage;
}

double tower_defense::Minion::getVelocity() const {
    return this->velocity;
}

int tower_defense::Minion::getReward() const {
    return this->reward;
}

int tower_defense::Minion::getHealth() const {
    return this->health;
}

void tower_defense::Minion::setHealth(int value) {
    this->health = value;
}
