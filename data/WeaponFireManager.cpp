#include "WeaponFireManager.h"
#include "../graphics/TextureManager.h"
#include "../exceptions.h"
#include "../include/pugixml/pugixml.hpp"
#include "../logic/Beam.h"
#include "../logic/Bullet.h"
#include "../logic/Ring.h"


using namespace data;
using namespace tower_defense;
using namespace std;
using namespace sf;
using namespace graphics;
using namespace pugi;

WeaponFireManager::WeaponFireManager() {

}

WeaponFireManager::~WeaponFireManager() {
	this->clear();
}

const WeaponFire& WeaponFireManager::getFire(int fireClass) const {
	map<int, WeaponFire*>::const_iterator it = this->fires.find(fireClass);
	if (it == this->fires.cend())
		FIRE_DOES_NOT_EXIST

	return *it->second;
}

const Texture &WeaponFireManager::getTexture(int fireClass) const {
	if (fireClass < 0 || fireClass >= nextClass)
		FIRE_DOES_NOT_EXIST

	const Texture& toRet = AppModel::getInstance().getTextures().get()->get(TextureManager::WEAPON_FIRE);
	AppModel::getInstance().getTextures().release();

	return toRet;
}

WeaponFire* WeaponFireManager::load(const string& directory, const std::string& name) {
	map<string, int>::iterator it = this->fireIds.find(name);
	if (it != this->fireIds.end())
		return fires[it->second];

	xml_document doc;
	if (!doc.load_file((directory + WEAPON_FIRES_LOCATION + name + ".xml").c_str(),
		pugi::parse_full | pugi::parse_trim_pcdata, pugi::encoding_utf8))
		return nullptr;

	xml_node fireNode = doc.child("weaponFire");

	AppModel::getInstance().getTextures().get()->add(graphics::TextureManager::WEAPON_FIRE, nextClass,
		directory + WEAPON_FIRES_LOCATION + fireNode.child_value("imgsrc"));
	AppModel::getInstance().getTextures().release();

	WeaponFire* toRet = nullptr;

	switch (fireNode.child_value("type")[1]) {
	case 'u':
		toRet = new Bullet(
			atoi(fireNode.child_value("damage")),
			atof(fireNode.child_value("size")),
			atoi(fireNode.child_value("hitOnlyFirst")),
			atof(fireNode.child_value("splash")),
			atoi(fireNode.child_value("velocity")),
			atoi(fireNode.child_value("lifeTime")),
			nextClass++);
	case 'e':
		toRet = new Beam(
			atoi(fireNode.child_value("damage")),
			atof(fireNode.child_value("size")),
			nextClass++,
			atoi(fireNode.child_value("hitOnlyFirst")));
	case 'i':
		toRet = new Ring(
			atoi(fireNode.child_value("damage")),
			atoi(fireNode.child_value("velocity")),
			atoi(fireNode.child_value("lifeTime")),
			nextClass++);
	}

	if (toRet != nullptr) {
		this->fireIds[name] = toRet->getObjClass();
		this->fires[toRet->getObjClass()] = toRet;
	}

	return toRet;
}

void WeaponFireManager::clear() {
	for (map<int, WeaponFire*>::iterator it = this->fires.begin(); it != this->fires.end(); it++) {
		delete it->second;
	}

	this->fireIds.clear();
	this->fires.clear();
	this->nextClass = 0;
}