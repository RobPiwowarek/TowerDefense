#include "Turret.h"


tower_defense::Turret::Turret(const int size, const int turretClass, const double rotationSpeed, const int level, const Weapon& wBase)
	: Entity(Point(), 0, size, turretClass)
{
	this->weapon = new Weapon(wBase, this);
	this->rotationSpeed = rotationSpeed;
	this->level = level;
}

tower_defense::Turret::Turret(const Turret& base, const Point& location)
	: Entity(base) {
	this->weapon = new Weapon(*base.weapon, this);
	this->location = location;
	this->level = base.level;
	this->rotationSpeed = base.rotationSpeed;
}

int tower_defense::Turret::getCurrentHealth() const { return this->currentHealth; }

int tower_defense::Turret::getMaxHealth() const { return this->maxHealth; }

bool tower_defense::Turret::receiveDamage(const int damage, Grid& g) {
    if (this->currentHealth <= 0) return false;
    else{
        this->currentHealth-=damage;
    }

    if (this->currentHealth <= 0) this->destroy(g);

    return true;
}

//TODO: implement
void tower_defense::Turret::destroy(Grid& g) {
    g.getElement(this->location).setTurret(nullptr);
}

void tower_defense::Turret::setCurrentHealth(int currentHealth) {
	if (currentHealth >= this->maxHealth){
		this->currentHealth = this->maxHealth;
	}
	else
		this->currentHealth = currentHealth;
}

tower_defense::Turret::~Turret()
{
	delete this->weapon;
}

double tower_defense::Turret::getRotationSpeed() const
{
	return this->rotationSpeed;
}

void tower_defense::Turret::setRotationSpeed(const double d)
{
	this->rotationSpeed = d;
	if (this->rotationSpeed < 0)
		this->rotationSpeed *= -1;
}


int tower_defense::Turret::getLevel() const
{
	return this->level;
}

void tower_defense::Turret::setLevel(int lvl)
{
	this->level = lvl;
}

tower_defense::Weapon& tower_defense::Turret::getWeapon()
{
	return *this->weapon;
}