#include "Item.h"

using namespace std;
string NameSlot(Slot slot){
    switch (slot){
        case Slot::Weapon:
        return "Оружие";
        case Slot::Shield:
        return "Щит";
        case Slot::Helmet:
        return "Шлем";
        case Slot::Armor:
        return "Броня";
        case Slot::Boots:
        return "Сапоги";
        case Slot::Ring:
        return "Кольцо";
        case Slot::Amulet:
        return "Амулеты";
    }
    return "ЧТО? НЕТ, ЗНАЧИТ УКРАЛИ";
}
Item::Item():slot(Slot::Weapon){}
Item::Item(const string& name, const string& lor, Slot slot, HaracteristicBONUS bonuses):name(name), lor(lor),slot(slot),bonuses(bonuses){}