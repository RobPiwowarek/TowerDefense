#include "Minion.h"

// TODO: czemu entity(point(0,0))?
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
}

tower_defense::Item* tower_defense::Minion::getItem() const { return this->item; }

bool tower_defense::Minion::hasItem() const { return this->item != nullptr; }

bool tower_defense::Minion::hasItem(tower_defense::Item* item) const { return this->item != item; }

bool tower_defense::Minion::setItem(tower_defense::Item* item) { this->item = item; }

bool tower_defense::Minion::isDead() const {
    return this->dead;
}

void tower_defense::Minion::death(Game &game) {
    this->dead = true;

    game.getPlayer().setMoney(this->reward);
    game.getMap().getGrid().getElement(this->location)->getMinions().erase(this);

    // todo: remove from collision manager
}

void tower_defense::Minion::chooseDestination(Grid &g, Game &game) {
    GridElement* currentLocation = g.getElement(this->location);
    GridElement* left = currentLocation->getLeftNeighbour(),
    *right = currentLocation->getRightNeighbour(), *up = currentLocation->getUpNeighbour(), *down = currentLocation->getDownNeighbour();

    this->next = nullptr;

    if (left != nullptr && left->getDistToTarget() != -1) {
        this->next = left;
        this->angle = 270.0f;
    }

    if (right != nullptr && right->getDistToTarget() != -1) if(right->getDistToTarget() < this->next->getDistToTarget()){} {
        this->next = right;
        this->angle = 90.0f;
    }

    if (up != nullptr && up->getDistToTarget() != -1) if (up->getDistToTarget() < this->next->getDistToTarget()) {
        this->next = up;
        this->angle = 0.0f;
    }

    if (down != nullptr && down->getDistToTarget() != -1) if (down->getDistToTarget() < this->next->getDistToTarget()) {
        this->next = down;
        this->angle = 180.0f;
    }
}

void tower_defense::Minion::refresh(Grid &g, Game &game) {
    if (this->health <= 0) {
        this->death(game);
    }

    if (g.getElement(this->location) == this->next)
        chooseDestination(g, game);

    // TODO:
    // if road is blocked attack nearest tower
    if (this->next == nullptr) {

    }

    // TODO: check if correct
    // Update location
    this->location.setX(this->location.getX() + this->velocity*sin(this->angle));
    this->location.setY(this->location.getY() - this->velocity*cos(this->angle));
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
