#include "Friend.h"
#include <iostream>

// namespace V1
bool V1::Tv::volUp() {
    if (volume >= VOLMAXVAL)
        return false;
    volume++;
    return true;
}

bool V1::Tv::volDown() {
    if (volume <= VOLMINVAL)
        return false;
    volume--;
    return true;
}

void V1::Tv::nextChan() {
    if (channel < maxChannel)
        channel++;
    else
        channel = 1;
}

void V1::Tv::preChan() {
    if (channel > 1)
        channel--;
    else
        channel = maxChannel;
}

void V1::Tv::displaySetting() const {
    using std::cout;
    using std::endl;
    cout << "TV state is " << (state == ON ? "ON" : "OFF") << endl;
    if (state == ON) {
        cout << "Volume setting = " << volume << endl;
        cout << "Channel setting = " << channel << endl;
        cout << "Mode = " << (mode == ANTENNA ? "Antenna" : "Cable") << endl;
        cout << "Input = " << (input == TV ? "TV" : "DVD") << endl;
    }
}

void V2::Tv::displaySetting() const {
    using std::cout;
    using std::endl;
    cout << "TV state is " << (state == ON ? "ON" : "OFF") << endl;
    if (state == ON) {
        cout << "Volume setting = " << volume << endl;
        cout << "Channel setting = " << channel << endl;
        cout << "Mode = " << (mode == ANTENNA ? "Antenna" : "Cable") << endl;
        cout << "Input = " << (input == TV ? "TV" : "DVD") << endl;
    }
}