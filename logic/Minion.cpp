#include "Minion.h"
#include <iostream>

#define PI 3.1415

// TODO: czemu entity(point(0,0))? Re: w sumie nie ma znaczenia, ale konstruktor wymaga jakiegos
tower_defense::Minion::Minion(
        const double velocity, const double size, const int minionClass,
        const int reward, const int health, const int damage, const TargetPriority priority, const int attackSpeed)
        : Entity(Point(0, 0), 0.0, size, minionClass) {
    this->velocity = velocity;
    this->reward = reward;
    this->health = health;
    this->next = nullptr;
    this->target = priority;

	this->damage = damage;
	this->attackSpeed = attackSpeed;
}

tower_defense::Minion::Minion(const Minion &base, const Point &x0)
        : Entity(base) {
    this->velocity = base.velocity;
    this->reward = base.reward;
    this->health = base.health;
    this->location = x0;
    this->next = nullptr;
	this->target = base.target;
	this->damage = base.damage;
	this->attackSpeed = base.attackSpeed;
	this->attackRefreshing = 0;
}

void tower_defense::Minion::attack(tower_defense::Turret &turret) {
	if (this->attackRefreshing) return;
    turret.attack(this->damage);
	this->attackRefreshing = this->attackSpeed;
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

    game.getPlayer().setMoney(game.getPlayer().getMoney() + this->reward);
}

#include <iostream>

void tower_defense::Minion::chooseDestination(Grid &g, Game &game) {
    GridElement* currentLocation = g.getElement(this->location);
    GridElement* left = currentLocation->getLeftNeighbour(),
		*right = currentLocation->getRightNeighbour(),
		*up = currentLocation->getUpNeighbour(),
		*down = currentLocation->getDownNeighbour();

    this->next = nullptr;

	if (currentLocation->getDistToCorner() != -1 && target == Escape) { // Go to corner
		int dist = currentLocation->getDistToCorner();

		if (dist == 0) {
			this->next = currentLocation;
			return;
		}
		if (left != nullptr)
			if (!left->hasTurret() && left->getDistToCorner() < dist) {
				this->next = left;
				this->angle = -PI / 2;
			}

		if (right != nullptr)
			if (!right->hasTurret() && right->getDistToCorner() < dist) {
				this->next = right;
				this->angle = PI / 2;
			}

		if (up != nullptr)
			if (!up->hasTurret() && up->getDistToCorner() < dist) {
				this->next = up;
				this->angle = 0.0f;
			}

		if (down != nullptr)
			if (!down->hasTurret() && down->getDistToCorner() < dist) {
				this->next = down;
				this->angle = PI;
			}

	}
    else if (currentLocation->getDistToTarget() != -1 && (target == Item || currentLocation->getDistToTurret() == -1
		|| (target == Closer &&	(currentLocation->getDistToTarget() <= currentLocation->getDistToTurret())))) { // Go to target
		int dist = currentLocation->getDistToTarget();
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
	if (this->attackRefreshing)
		this->attackRefreshing--;

	if (this->next == nullptr || this->next == g.getElement(this->location))
		this->chooseDestination(g, game);
	else if (this->next->hasTurret() && this->target != Turret)
			this->chooseDestination(g, game);

	if (this->next != nullptr)
		if (this->next->hasTurret())
			this->attack(*this->next->getTurret());

    if (this->target == Item) {
		if (g.getElement(this->location)->hasItem()){
			
			tower_defense::Item* i = *g.getElement(this->location)->getItems().begin();
			i->pickUp(this, g);
			
			g.calculateDistance(Grid::Item);
			g.calculateDistance(Grid::Escape);
		}
    }

    // Update location
	if (this->next != nullptr) {
		Point newLocation = location + 
			Point{this->velocity*sin(this->angle), -this->velocity*cos(this->angle)};
		if (g.getElement(newLocation) != next || !next->hasTurret())
			this->location = newLocation;
	}
	
	if (this->hasItem())
		this->item->setLocation(this->location);

	if (g.getElement(this->location) == this->next)
		this->next = nullptr;
}

tower_defense::Minion::TargetPriority tower_defense::Minion::getTargetPriority() const{
	return this->target;
}

void tower_defense::Minion::setTargetPriority(tower_defense::Minion::TargetPriority target){
	this->target = target;
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
