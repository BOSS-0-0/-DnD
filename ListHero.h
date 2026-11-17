#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Haracteristic.h"
#include "Item.h"
#include "ClassFeature.h"
#include "HaracterClass.h"

class ListHero {
private:
    std::string name;
    std::unique_ptr<HaracterClass> haracterClass;
    std::string lor;
    std::string avatarFoto;
    int level;
    int xp;
    int freePoint;
    BaseHaracteristic baseScore;
    std::map<Slot, Item> equiment;
    std::vector<Item> invetory;
    std::vector<std::string> information;
    std::vector<ClassFeature> learnedFeatures;
    std::vector<ClassFeature> recentLearned;

    void addNotification(const std::string& message);
    bool hasFeature(const std::string& featureName) const;
    void learnFeaturesForLevel(int newLevel);
    int xpForNextLevel() const;
    void levelUp();

public:
    ListHero(
        const std::string& name,
        std::unique_ptr<HaracterClass> haracterClass,
        BaseHaracteristic scores
    );

    void setLor(const std::string& text);
    void setAvatarFoto(const std::string& path);

    std::string className() const;
    int getLevel() const;
    int getFreePoint() const;

    static int modifierFromScore(int score);

    int proficiencyBonus() const;
    int itemBonus(Haracteristic h) const;
    int totalScore(Haracteristic h) const;
    int baseModifier(Haracteristic h) const;
    int totalModifier(Haracteristic h) const;
    int rollBonus(Haracteristic h, bool proficient) const;

    void addItem(const Item& item);
    bool equipItem(const std::string& itemName);
    void unequipItem(Slot slot);

    void addExperience(int amount);
    void spendAbilityPoint(Haracteristic h);

    void printAndClearNotifications();
    void printAndClearRecentLearned();
    void printSheet() const;
};