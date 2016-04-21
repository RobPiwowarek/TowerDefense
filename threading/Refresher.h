#ifndef REFRESHER_H
#define REFRESHER_H

#include <mutex>
#include <thread>
#include "..\logic\Game.h"

class Refresher {
public:
    /// creates a new instance of refresher that will
    /// refresh the game's engine
    Refresher();

    ~Refresher();

    /// starts refresher if is not going, else does nothing
    void start();

    /// stops refresher if is going, else does nothing
    void stop();

    /// returns time between refreshes in miliseconds
    int getInterval() const;

    /// sets time between refreshes in miliseconds
    void setInterval(int interval);

    /// returns if the refresher has been started
    bool isGoing() const;

private:
    std::mutex startStopMutex;

    std::mutex goingMutex;
    bool going;
    std::mutex intervalMutex;
    int interval;

    std::thread *thread;

    void refresh();

};

#endif