#include "Friend.h"
#include "iostream"

void testV1();
void testV2();

int main() {
    testV1();
    testV2();
}

void testV1() {
    V1::Tv tv1;
    V1::Remote remote1;

    tv1.displaySetting();

    if (!tv1.isOn()) {
        std::cout << "Starting...\n";
        remote1.switchOnOff(tv1); // 开机
        tv1.displaySetting();
    }

    std::cout << "Switching TV channel...\n";
    remote1.setChan(tv1, 33);
    tv1.displaySetting();
}

void testV2() {
    V2::Tv tv2;
    V2::Remote remote2;

    tv2.displaySetting();

    if (!tv2.isOn()) {
        std::cout << "Starting...\n";
        remote2.switchOnOff(tv2);
        tv2.displaySetting();
    }

    std::cout << "Switching TV channel...\n";
    remote2.setChan(tv2, 44);
    tv2.displaySetting();
}