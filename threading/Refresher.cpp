#include "Refresher.h"
#include <thread>

Refresher::Refresher() {
    this->going = false;
    this->interval = 100;

    this->thread = nullptr;
}

#include <iostream>
Refresher::~Refresher() {
	if (this->thread != nullptr)
		this->stop();
	std::cout << "[~GM]\n";
    this->goingMutex.lock();
	this->goingMutex.unlock();
	std::cout << "[~IM]\n";
    this->intervalMutex.lock();
    this->intervalMutex.unlock();
}

void Refresher::start() {
    this->startStopMutex.lock();

    this->goingMutex.lock();
    if (!this->going) {
        this->going = true;
        this->thread = new std::thread(&Refresher::refresh, this);
    }
    this->goingMutex.unlock();

    this->startStopMutex.unlock();
}

void Refresher::stop() {
	std::cout << "[sSM]\n";
    this->startStopMutex.lock();

	std::cout << "[sGM]\n";
    this->goingMutex.lock();
    if (this->going) {
		this->going = false;
		this->goingMutex.unlock();
        this->thread->join();
        delete this->thread;
		this->thread = nullptr;
    }
	else this->goingMutex.unlock();
	std::cout << "[\\GM]\n";

	this->startStopMutex.unlock();
	std::cout << "[\\SM]\n";
}

int Refresher::getInterval() const {
    return this->interval;
}

void Refresher::setInterval(int interval) {
    if (interval > 0) {
        this->intervalMutex.lock();
        this->interval = interval;
        this->intervalMutex.unlock();
    }
}

bool Refresher::isGoing() const {
    return this->going;
}

void Refresher::refresh() {
	srand(time(NULL));
    while (true) {
        this->goingMutex.lock();
		if (!going) {
			this->goingMutex.unlock();
			break;
		}
        this->goingMutex.unlock();

        this->intervalMutex.lock();
        int interval = this->interval;
        this->intervalMutex.unlock();

        //refresh game in new thread
        std::thread gameRefresh(&Refresher::refreshGame, this, rand());

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));

        //wait for game refreshing thread if not finished yet
        gameRefresh.join();
    }
}

#define DEBUG

void Refresher::refreshGame(int rSeed) {
#ifndef DEBUG
	try {
#endif
		srand(rSeed);
		AppModel::getInstance().getGame().get()->refresh();
		AppModel::getInstance().getGame().release();
#ifndef DEBUG
	}
	catch (std::exception e) {
		std::cout << "Refr ecx: " << e.what() << std::endl;
	}
	catch (int i) {
		std::cout << "Refr ecx: " << i;
	}
	catch (...) {
		std::cout << "Refr ecx\n";
	}
#endif
}