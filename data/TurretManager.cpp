#include "TurretManager.h"
#include "WeaponFireManager.h"

#include "../graphics/TextureManager.h"

#include "../logic/Beam.h"
#include "../logic/Bullet.h"
#include "../logic/Ring.h"

#include "../include/pugixml/pugixml.hpp"

#include "../exceptions.h"


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
	this->weaponFireLists.clear();
	this->costs.clear();
	this->nextClass = 0;
}

Turret *TurretManager::addTurret(const string &path, const string &file) {
	pair<Turret*, pair<string, int> > t = load(path, file);

	if (t.first == nullptr)
		return nullptr;

	this->turrets[t.first->getObjClass()] = t.first;
	this->names[t.first->getObjClass()] = t.second.first;
	this->costs[t.first->getObjClass()] = t.second.second;

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

pair<Turret*, pair<string, int> > TurretManager::load(const string &directory, const string &file) {
	xml_document doc;

	if (!doc.load_file((directory + TURRET_LOCATION + file + ".xml").c_str(),
		pugi::parse_full | pugi::parse_trim_pcdata, pugi::encoding_utf8))
		return make_pair(nullptr, make_pair(string(), 0));


	xml_node turretNode = doc.child("turret");

	AppModel::getInstance().getTextures().get()->add(graphics::TextureManager::TURRET, nextClass,
		directory + TURRET_LOCATION + turretNode.child_value("imgsrc"));
	AppModel::getInstance().getTextures().release();
	string name = turretNode.child_value("name");
	int cost = atoi(turretNode.child_value("cost"));
	double size = atof(turretNode.child_value("size"));

	double rotationSpeed = atof(turretNode.child_value("rotationSpeed"));
	int health = atoi(turretNode.child_value("health"));

	pair<Turret*, pair<string, int> > toRet = 
		make_pair(new Turret(size, nextClass, rotationSpeed, 0, *this->load(turretNode.child("weapon"), directory, nextClass)),
		make_pair(name, cost));
	nextClass++;

	return toRet;
}

Weapon* TurretManager::load(const xml_node& weaponNode, const string& directory, int turretObjClass) {
	int reloadTime = atoi(weaponNode.child_value("reloadTime"));
	double range = atof(weaponNode.child_value("range"));

	WeaponFireList* wfl = new WeaponFireList();

	xml_object_range<xml_named_node_iterator> fires = weaponNode.children("weaponFire");
	WeaponFire* next;

	WeaponFireManager* fireManager = AppModel::getInstance().getWeaponFireManager().get();

	for (xml_named_node_iterator it = fires.begin(); it != fires.end(); it++)
		if (next = fireManager->load(directory, it->child_value()))
			wfl->push_back(make_pair(it->attribute("time").as_int(),
			make_pair(next, it->attribute("angleMod").as_double())));

	AppModel::getInstance().getWeaponFireManager().release();

	return new Weapon(range, reloadTime, wfl);
}

int TurretManager::getCost(int turretClass) const {
	map<int, int>::const_iterator it = this->costs.find(turretClass);
	if (it == this->costs.cend())
		NO_SUCH_TURRET

	return it->second;
}

void TurretManager::getTurrets(vector<pair<int, pair<string, int> > >& turretList) const {
	turretList.clear();

	for (int i = 0; i < nextClass; i++)
		turretList.push_back(make_pair(i, make_pair(this->names.find(i)->second, this->costs.find(i)->second)));
}