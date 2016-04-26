#include "TurretManager.h"
#include "../graphics/TextureManager.h"

#include "../logic/Beam.h"
#include "../logic/Bullet.h"
#include "../logic/Ring.h"

#include "../include/pugixml/pugixml.hpp"

#include <exception>

#define NO_SUCH_TURRET throw ("Exception: turret does not exist");

using namespace std;
using namespace sf;
using namespace pugi;
using namespace data;
using namespace tower_defense;

TurretManager::~TurretManager() {
	this->clear();
}

void TurretManager::clear() {
	for (map<int, Turret*>::iterator it = this->turrets.begin(); it != this->turrets.end(); it++)
		delete it->second;

	this->turrets.clear();
	this->names.clear();
	this->nextClass = 0;
}

Turret *TurretManager::addTurret(const string &path, const string &file) {
	pair<Turret*, string> t = load(path + TURRET_LOCATION, file + ".xml");

	if (t.first == nullptr)
		return nullptr;

	this->turrets[t.first->getObjClass()] = t.first;
	this->names[t.first->getObjClass()] = t.second;

	return t.first;
}

const tower_defense::Turret &TurretManager::getTurret(int turretClass) const {
	map<int, Turret*>::const_iterator it = this->turrets.find(turretClass);
	if (it == this->turrets.cend())
		NO_SUCH_TURRET

	return *it->second;
}

const sf::Texture &TurretManager::getTexture(int turretClass) const {
	if (turretClass >= nextClass || turretClass < 0)
		NO_SUCH_TURRET

	const Texture& texture = AppModel::getInstance().getTextures().get()->get(graphics::TextureManager::TURRET, turretClass);
	AppModel::getInstance().getTextures().release();

	return texture;
}

const string &TurretManager::getName(int turretClass) const {
	map<int, string>::const_iterator it = this->names.find(turretClass);
	if (it == this->names.cend())
		NO_SUCH_TURRET

	return it->second;
}

pair<Turret*, string> TurretManager::load(const string &directory, const string &file) {
	xml_document doc;

	if (!doc.load_file((directory + TURRET_LOCATION + file).c_str(),
		pugi::parse_default | pugi::parse_trim_pcdata, pugi::encoding_utf8))
		return make_pair(nullptr, string());

	xml_node turretNode = doc.child("turret");

	AppModel::getInstance().getTextures().get()->add(graphics::TextureManager::TURRET, nextClass,
		directory + TURRET_LOCATION + turretNode.child_value("imgsrc"));

	string name = turretNode.child_value("name");
	double size = atof(turretNode.child_value("size"));
	double rotationSpeed = atof(turretNode.child_value("rotationSpeed"));
	int health = atoi(turretNode.child_value("health"));

	pair<Turret*, string> toRet = 
		make_pair(new Turret(size, nextClass, rotationSpeed, 0, *this->load(turretNode.child("weapon"), directory, nextClass)), name);
	nextClass++;

	return toRet;
}

Weapon* TurretManager::load(const xml_node& weaponNode, const string& directory, int turretObjClass) {
	int reloadTime = atoi(weaponNode.child_value("reloadTime"));
	double range = atof(weaponNode.child_value("range"));

	WeaponFireList* wfl = new WeaponFireList();

	xml_object_range<xml_named_node_iterator> fires = weaponNode.children("weaponFire");
	WeaponFire* next;
	for (xml_named_node_iterator it = fires.begin(); it != fires.end(); it++)
		if (next = this->loadWeaponFire(*it, directory))
			wfl->push_back(make_pair(atoi(it->child_value("fireTime")), next));

	this->weaponFireLists[turretObjClass];

	return new Weapon(range, reloadTime, wfl);
}

WeaponFire* TurretManager::loadWeaponFire(const xml_node& weaponFireNode, const string& directory) {
	AppModel::getInstance().getTextures().get()->add(graphics::TextureManager::WEAPON_FIRE, nextWeaponFireClass,
		directory + WEAPON_FIRES_LOCATION + weaponFireNode.child_value("imgsrc"));
	
	switch (weaponFireNode.child_value("type")[1]) {
	case 'u':
		return new Bullet(
			atoi(weaponFireNode.child_value("damage")),
			atof(weaponFireNode.child_value("size")),
			atoi(weaponFireNode.child_value("hitOnlyFirst")),
			atof(weaponFireNode.child_value("splash")),
			atoi(weaponFireNode.child_value("velocity")),
			atoi(weaponFireNode.child_value("lifeTime")),
			nextWeaponFireClass++);
	case 'e':
		return new Beam(
			atoi(weaponFireNode.child_value("damage")),
			atof(weaponFireNode.child_value("size")),
			nextWeaponFireClass++,
			atoi(weaponFireNode.child_value("hitOnlyFirst")));
	case 'i':
		return new Ring(
			atoi(weaponFireNode.child_value("damage")),
			atoi(weaponFireNode.child_value("velocity")),
			atoi(weaponFireNode.child_value("lifeTime")),
			nextWeaponFireClass++);
	}
}