#include "MinionWaveManager.h"
#include "MinionManager.h"

#include "../threading/AppModel.h"
#include "../exceptions.h"

#include "../include/pugixml/pugixml.hpp"


using namespace data;
using namespace tower_defense;
using namespace std;
using namespace pugi;


void MinionWaveManager::clear() {
    for (int i = 0; i < this->waves.size(); i++)
        delete this->waves[i];

    this->waves.clear();
}

void MinionWaveManager::load(const string &directory, const vector<string> &waves, graphics::TextureManager* tm) {
	MinionWave *cur;
    for (int i = 0; i < waves.size(); i++)
		if (cur = this->loadWave(directory, waves[i], tm))
            this->waves.push_back(cur);
}

const MinionWave &MinionWaveManager::get(int i) const {
	if (this->waves.size() <= i || i < 0)
		WAVE_DOES_NOT_EXIST

    return *this->waves[i];
}

const int MinionWaveManager::count() const {
    return this->waves.size();
}

MinionWaveManager::~MinionWaveManager() {
    this->clear();
}

MinionWave *MinionWaveManager::loadWave(const string &directory, const string &name, graphics::TextureManager* tm) {
    xml_document waveDoc;
    if (!waveDoc.load_file((directory + WAVE_LOCATION + name + ".xml").c_str(),
                           pugi::parse_default | pugi::parse_trim_pcdata, pugi::encoding_utf8))
        return nullptr;

    xml_node wave = waveDoc.child("wave");


    int timeBetweenMinions = atoi(wave.child_value("timeBetweenMinions"));
    queue<Minion *> minions;

    xml_object_range<xml_named_node_iterator> minionNodes = wave.children("minion");

    Minion *cur;

    MinionManager *manager = AppModel::getInstance().getMinionManager().get();

    for (xml_named_node_iterator it = minionNodes.begin(); it != minionNodes.end(); it++)
		if (cur = manager->addMinion(directory, it->child_value(), tm)) {
			if (it->attribute("count").empty())
				minions.push(cur);
			else
				for (int i = 0; i < it->attribute("count").as_int(); i++)
					minions.push(cur);
		}

    AppModel::getInstance().getMinionManager().release();

    return new MinionWave(minions, timeBetweenMinions);
}