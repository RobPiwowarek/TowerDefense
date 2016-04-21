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

bool tower_defense::Minion::isDead() const {
    return this->dead;
}

void tower_defense::Minion::death(Game &game) {
    this->dead = true;

    game.getPlayer().setMoney(this->reward);
    game.getMap().getGrid().getElement(this->location).getMinions().erase(this);

    // todo: remove from collision manager
}

// TODO: implement
void tower_defense::Minion::chooseDestination(Grid &g, Game &game) {


    // podejdz do przedmiotu jak najblizej sie da
    // jesli droga nie jest przyblokowana to podnies przedmiot i zacznij zawracac
    // w przeciwnym wypadku idz do najblizszego turreta
}

void tower_defense::Minion::refresh(Grid &g, Game &game) {

    if (this->health <= 0) {
        this->death(game);
    }

    // TODO: choose next target/location
    chooseDestination(g, game);
    // attack turret/pickup item?



    // Update location
    this->getLocation().setPoint(this->next->getLocation());
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
