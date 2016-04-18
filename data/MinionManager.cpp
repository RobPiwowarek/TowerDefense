#include "MinionManager.h"

#include "../threading/AppModel.h"
#include "../threading/ResourceManager.h"
#include "../graphics/TextureManager.h"

#define NO_MINION_EXCEPTION throw exception("Exception: No such minion");

using namespace std;
using namespace data;
using namespace tower_defense;
using namespace sf;

void MinionManager::clear() {
	for (map<int, Minion*>::iterator it = this->minions.begin();
		it != this->minions.end(); it++) {
		delete it->second;
	}
	this->minions.clear();
	this->minionClasses.clear();
	this->textures.clear();
	this->nextClass = 0;
}
int MinionManager::addMinion(const string& name) {
	map<string, int>::iterator it = this->minionClasses.find(name);
	if (it != this->minionClasses.end())
		return it->second;

	Minion* minion = this->load(name);
	if (minion == nullptr)
		return -1;

	this->minionClasses[name] = nextClass;
	this->minions[nextClass] = minion;
	return this->nextClass++;
}

const Minion& MinionManager::getMinion(const string& name) const {
	map<string, int>::const_iterator it = this->minionClasses.find(name);

	if (it == this->minionClasses.cend())
		NO_MINION_EXCEPTION

	return *this->minions.find(it->second)->second;
}

const Minion& MinionManager::getMinion(int minionClass) const {
	map<int, Minion*>::const_iterator it = this->minions.find(minionClass);

	if (it == this->minions.cend())
		NO_MINION_EXCEPTION

	return *it->second;
}

const Texture& MinionManager::getTexture(int minionClass) const {
	if (minionClass >= nextClass || minionClass < 0)
		NO_MINION_EXCEPTION

	ResourceManager<graphics::TextureManager>& textures = AppModel::getInstance().getTextures();

	const Texture& toRet = textures.get()->get(this->textures.find(minionClass)->second);

	textures.release();

	return toRet;
}

Minion* MinionManager::load(std::string source) {
	//TODO
	return nullptr;
}