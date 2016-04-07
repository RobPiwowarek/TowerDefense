#include "Refresher.h"
#include <thread>

Refresher::Refresher() {
	this->going = false;
	this->interval = 50;

	this->thread = nullptr;
}
Refresher::~Refresher() {
	this->goingMutex.lock();
	this->goingMutex.unlock();
	this->intervalMutex.lock();
	this->intervalMutex.unlock();

	if (this->thread != nullptr)
		this->stop();
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
	this->startStopMutex.lock();

	this->goingMutex.lock();
	if (this->going) {
		this->going = false;
		this->goingMutex.unlock();
		this->thread->join();
		delete this->thread;
		this->thread = nullptr;
	}
	else this->goingMutex.unlock();

	this->startStopMutex.unlock();
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
	while (true) {
		this->goingMutex.lock();
		if (!going) break;
		this->goingMutex.unlock();
		
		this->intervalMutex.lock();
		int interval = this->interval;
		this->intervalMutex.unlock();

		//refresh game in new thread
		std::thread gameRefresh/*(&Game::refresh)*/;

		std::this_thread::sleep_for(std::chrono::milliseconds(interval));

		//wait for game refreshing thread if not finished yet
		gameRefresh.join();
	}
}