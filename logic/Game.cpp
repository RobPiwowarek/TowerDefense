#include "Game.h"

tower_defense::Game::Game(Map m, MinionWave w, Player p): map(m), wave(w), player(p) {

}

tower_defense::Map& tower_defense::Game::getMap(){
    return this->map;
}

tower_defense::MinionWave& tower_defense::Game::getCurrentWave() {
    return this->wave;
}

tower_defense::Player& tower_defense::Game::getPlayer() {
    return this->player;
}

void tower_defense::Game::refresh() {
    this->map.refresh(this->player);
    this->wave.refresh();
}