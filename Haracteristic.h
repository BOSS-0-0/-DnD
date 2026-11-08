#pragma once
#include <string>
#include <vector>

enum class Haracteristic {
    STR,
    DEX,
    CON,
    INT,
    WIS,
    CHA
};
std::string NameHaracteristic(Haracteristic haracter);
std::string signedValue(int value);
struct BaseHaracteristic {
    int str = 10;
    int dex = 10;
    int con = 10;
    int int_ = 10;
    int wis = 10;
    int cha = 10;

    int get(Haracteristic haracter) const;
    void add(Haracteristic haracter, int value);
};

struct HaracteristicBONUS {
    int str = 0;
    int dex = 0;
    int con = 0;
    int int_ = 0;
    int wis = 0;
    int cha = 0;

    int get(Haracteristic haracter) const;
    void add(Haracteristic haracter, int value);
};
std::string BonusText(const HaracteristicBONUS& bonus);