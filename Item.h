#pragma once
#include <string>
#include "Haracteristic.h"

enum class Slot{
  Weapon,
  Shield,
  Helmet,
  Armor,
  Boots,
  Ring,
  Amulet  
};
std::string NameSlot(Slot slot);
struct Item{
    std::string name;//название предмета
    std::string lor;// его лор или описание
    Slot slot;//какой слот занимает 
    HaracteristicBONUS bonuses;//его бонус
    Item();
    Item(const std::string& name, const std::string& lor, Slot slot, HaracteristicBONUS bonuses = HaracteristicBONUS());
};