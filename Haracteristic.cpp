#include "Haracteristic.h"


std::string NameHaracteristic(Haracteristic haracter) {
    switch (haracter) {
        case Haracteristic::STR:
            return "Power";
        case Haracteristic::DEX:
            return "Dexterity";
        case Haracteristic::CON:
            return "Physique";
        case Haracteristic::INT:
            return "Intellect";
        case Haracteristic::WIS:
            return "Wisdom";
        case Haracteristic::CHA:
            return "Charisma";
    }
    return "ЧТО?";
}
std::string signedValue(int value) {
    if (value > 0) {
        return "+" + std::to_string(value);
    }
    return std::to_string(value);
}
int BaseHaracteristic::get(Haracteristic haracter) const {
    switch (haracter) {
        case Haracteristic::STR:
            return str;
        case Haracteristic::DEX:
            return dex;
        case Haracteristic::CON:
            return con;
        case Haracteristic::INT:
            return int_;
        case Haracteristic::WIS:
            return wis;
        case Haracteristic::CHA:
            return cha;
    }
    return 101;
}
void BaseHaracteristic::add(Haracteristic haracter, int value) {
    switch (haracter) {
        case Haracteristic::STR:
            str += value;
            break;
        case Haracteristic::DEX:
            dex += value;
            break;
        case Haracteristic::CON:
            con += value;
            break;
        case Haracteristic::INT:
            int_ += value;
            break;
        case Haracteristic::WIS:
            wis += value;
            break;
        case Haracteristic::CHA:
            cha += value;
            break;
    }
}
int HaracteristicBONUS::get(Haracteristic haracter) const {
    switch (haracter) {
        case Haracteristic::STR:
            return str;
        case Haracteristic::DEX:
            return dex;
        case Haracteristic::CON:
            return con;
        case Haracteristic::INT:
            return int_;
        case Haracteristic::WIS:
            return wis;
        case Haracteristic::CHA:
            return cha;
    }
    return 0;
}
void HaracteristicBONUS::add(Haracteristic haracter, int value) {
    switch (haracter) {
        case Haracteristic::STR:
            str += value;
            break;
        case Haracteristic::DEX:
            dex += value;
            break;
        case Haracteristic::CON:
            con += value;
            break;
        case Haracteristic::INT:
            int_ += value;
            break;
        case Haracteristic::WIS:
            wis += value;
            break;
        case Haracteristic::CHA:
            cha += value;
            break;
    }
}
std::string BonusText(const HaracteristicBONUS& bonus) {
    std::vector<std::string> parts;
    parts.reserve(6);
    parts.push_back(
        NameHaracteristic(Haracteristic::STR) +
        " " +
        signedValue(bonus.str)
    );
    parts.push_back(
        NameHaracteristic(Haracteristic::DEX) +
        " " +
        signedValue(bonus.dex)
    );
    parts.push_back(
        NameHaracteristic(Haracteristic::CON) +
        " " +
        signedValue(bonus.con)
    );
    parts.push_back(
        NameHaracteristic(Haracteristic::INT) +
        " " +
        signedValue(bonus.int_)
    );
    parts.push_back(
        NameHaracteristic(Haracteristic::WIS) +
        " " +
        signedValue(bonus.wis)
    );
    parts.push_back(
        NameHaracteristic(Haracteristic::CHA) +
        " " +
        signedValue(bonus.cha)
    );
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) {
            result += ", ";
        }
        result += parts[i];
    }

    return result;
}