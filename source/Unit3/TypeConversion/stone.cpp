#include "stone.h"
Stone::Stone() {
    stone = pds_left = pounds = 0;
}
Stone::Stone(double p) {
    pounds = p;
    stone = (int) p / LBS_PER_STN;
    pds_left = p - stone * LBS_PER_STN;
}

Stone::Stone(int s, double pl) {
    stone = s;
    pds_left = pl;
    pounds = s * LBS_PER_STN + pl;
}

Stone::~Stone() {
    std::cout << "Destructor.\n";
}

void Stone::show_stn() const {
    std::cout << stone << " stone, " << pds_left << " pounds\n";
}

void Stone::show_lbs() const {
    std::cout << pounds << " pounds.\n";
}

Stone::operator double() const {
    return pounds;
}