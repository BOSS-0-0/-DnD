#include "ListHero.h"

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

ListHero::ListHero(
    const string& name,
    unique_ptr<HaracterClass> haracterClass,
    BaseHaracteristic scores
)
    : name(name),
      haracterClass(move(haracterClass)),
      lor(""),
      avatarFoto(""),
      level(1),
      xp(0),
      freePoint(0),
      baseScore(scores) {
    learnFeaturesForLevel(level);
}

void ListHero::setLor(const string& text) {
    lor = text;
    addNotification("История персонажа обновлена.");
}

void ListHero::setAvatarFoto(const string& path) {
    avatarFoto = path;
    addNotification("Аватар обновлён: " + path);
}

string ListHero::className() const {
    if (haracterClass) {
        return haracterClass->name();
    }

    return "Класс не указан";
}

int ListHero::getLevel() const {
    return level;
}

int ListHero::getFreePoint() const {
    return freePoint;
}

int ListHero::modifierFromScore(int score) {
    if (score >= 10) {
        return (score - 10) / 2;
    }

    return (score - 11) / 2;
}

int ListHero::proficiencyBonus() const {
    return 2 + (level - 1) / 4;
}

void ListHero::addNotification(const string& message) {
    information.push_back(message);
}

bool ListHero::hasFeature(const string& featureName) const {
    return any_of(
        learnedFeatures.begin(),
        learnedFeatures.end(),
        [&](const ClassFeature& feature) {
            return feature.name == featureName;
        }
    );
}

void ListHero::learnFeaturesForLevel(int newLevel) {
    if (!haracterClass) {
        return;
    }

    vector<ClassFeature> features = haracterClass->featuresAt(newLevel);

    for (const auto& feature : features) {
        if (!hasFeature(feature.name)) {
            learnedFeatures.push_back(feature);
            recentLearned.push_back(feature);

            if (feature.isSpell) {
                addNotification("Новое заклинание: " + feature.name);
            } else {
                addNotification("Новое умение: " + feature.name);
            }
        }
    }
}

int ListHero::xpForNextLevel() const {
    return level * 100;
}

void ListHero::levelUp() {
    ++level;

    addNotification(
        "Уровень повышен! Текущий уровень: " + to_string(level)
    );

    if (
        level == 4 ||
        level == 8 ||
        level == 12 ||
        level == 16 ||
        level == 19
    ) {
        freePoint += 2;
        addNotification("Получено 2 свободных очка характеристик.");
    }

    learnFeaturesForLevel(level);
}

int ListHero::itemBonus(Haracteristic h) const {
    int total = 0;

    for (const auto& pair : equiment) {
        total += pair.second.bonuses.get(h);
    }

    return total;
}

int ListHero::totalScore(Haracteristic h) const {
    return baseScore.get(h) + itemBonus(h);
}

int ListHero::baseModifier(Haracteristic h) const {
    return modifierFromScore(baseScore.get(h));
}

int ListHero::totalModifier(Haracteristic h) const {
    return modifierFromScore(totalScore(h));
}

int ListHero::rollBonus(Haracteristic h, bool proficient) const {
    int bonus = totalModifier(h);

    if (proficient) {
        bonus += proficiencyBonus();
    }

    return bonus;
}

void ListHero::addItem(const Item& item) {
    invetory.push_back(item);
    addNotification("Предмет добавлен в инвентарь: " + item.name);
}

bool ListHero::equipItem(const string& itemName) {
    auto it = find_if(
        invetory.begin(),
        invetory.end(),
        [&](const Item& item) {
            return item.name == itemName;
        }
    );

    if (it == invetory.end()) {
        addNotification("Предмет не найден: " + itemName);
        return false;
    }

    Item item = *it;
    invetory.erase(it);

    auto equipped = equiment.find(item.slot);

    if (equipped != equiment.end()) {
        invetory.push_back(equipped->second);
        equiment.erase(equipped);
        addNotification("Снят предмет со слота: " + NameSlot(item.slot));
    }

    equiment[item.slot] = item;
    addNotification("Предмет надет: " + item.name);

    return true;
}

void ListHero::unequipItem(Slot slot) {
    auto it = equiment.find(slot);

    if (it == equiment.end()) {
        addNotification("Слот пуст: " + NameSlot(slot));
        return;
    }

    invetory.push_back(it->second);
    addNotification("Предмет снят: " + it->second.name);
    equiment.erase(it);
}

void ListHero::addExperience(int amount) {
    xp += amount;
    addNotification("Получено опыта: " + to_string(amount));

    while (xp >= xpForNextLevel()) {
        xp -= xpForNextLevel();
        levelUp();
    }
}

void ListHero::spendAbilityPoint(Haracteristic h) {
    if (freePoint <= 0) {
        addNotification("Нет свободных очков характеристик.");
        return;
    }

    baseScore.add(h, 1);
    --freePoint;

    addNotification(
        "Характеристика " +
        NameHaracteristic(h) +
        " повышена до " +
        to_string(baseScore.get(h))
    );
}

void ListHero::printAndClearNotifications() {
    cout << "\n=== УВЕДОМЛЕНИЯ ===\n";

    if (information.empty()) {
        cout << "Новых уведомлений нет.\n";
    } else {
        for (const auto& message : information) {
            cout << "- " << message << "\n";
        }
    }

    information.clear();
}

void ListHero::printAndClearRecentLearned() {
    cout << "\n=== НОВОЕ ПРИ ПОВЫШЕНИИ УРОВНЯ ===\n";

    if (recentLearned.empty()) {
        cout << "Новых умений или заклинаний нет.\n";
    } else {
        for (const auto& feature : recentLearned) {
            if (feature.isSpell) {
                cout << "[Заклинание] ";
            } else {
                cout << "[Умение] ";
            }

            cout << feature.name << "\n";
            cout << "Уровень: " << feature.level << "\n";
            cout << feature.description << "\n";
            cout << "--------------------------------------\n";
        }
    }

    recentLearned.clear();
}

void ListHero::printSheet() const {
    cout << "\n";
    cout << "=====================================\n";
    cout << "ЛИСТ ГЕРОЯ\n";
    cout << "=====================================\n";

    cout << "Имя: " << name << "\n";
    cout << "Класс: " << className() << "\n";
    cout << "Уровень: " << level << "\n";
    cout << "Опыт: " << xp << "\n";
    cout << "Бонус мастерства: +" << proficiencyBonus() << "\n";
    cout << "Свободные очки: " << freePoint << "\n";

    cout << "\nАватар: " << avatarFoto << "\n";
    cout << "История: " << lor << "\n";

    cout << "\nХарактеристики:\n";

    vector<Haracteristic> abilities = {
        Haracteristic::STR,
        Haracteristic::DEX,
        Haracteristic::CON,
        Haracteristic::INT,
        Haracteristic::WIS,
        Haracteristic::CHA
    };

    for (Haracteristic h : abilities) {
        int base = baseScore.get(h);
        int item = itemBonus(h);
        int total = totalScore(h);

        int baseMod = modifierFromScore(base);
        int totalMod = modifierFromScore(total);

        cout << "\n" << NameHaracteristic(h) << ":\n";
        cout << "  База: " << base;

        if (item != 0) {
            cout << " | Предмет: " << signedValue(item);
        }

        cout << " | Итог: " << total << "\n";
        cout << "  Модификатор: " << signedValue(totalMod);

        if (totalMod != baseMod) {
            cout << "  *** МОДИФИКАТОР ИЗМЕНЁН ПРЕДМЕТАМИ ***";
        } else if (item != 0) {
            cout << "  [есть бонус от предмета]";
        }

        cout << "\n";
        cout << "  Бросок с профом: "
             << signedValue(rollBonus(h, true))
             << "\n";
    }

    cout << "\nЭкипировка:\n";

    if (equiment.empty()) {
        cout << "Нет надетых предметов.\n";
    } else {
        for (const auto& pair : equiment) {
            cout << NameSlot(pair.first) << ": "
                 << pair.second.name << "\n";
            cout << "  Бонусы: " << BonusText(pair.second.bonuses) << "\n";
        }
    }

    cout << "\nИнвентарь:\n";

    if (invetory.empty()) {
        cout << "Инвентарь пуст.\n";
    } else {
        for (const auto& item : invetory) {
            cout << "- " << item.name
                 << " (" << NameSlot(item.slot) << ")\n";
        }
    }

    cout << "\nИзвестные умения и заклинания:\n";

    if (learnedFeatures.empty()) {
        cout << "Нет известных умений или заклинаний.\n";
    } else {
        for (const auto& feature : learnedFeatures) {
            if (feature.isSpell) {
                cout << "[Заклинание] ";
            } else {
                cout << "[Умение] ";
            }

            cout << feature.name
                 << " (ур. " << feature.level << ")\n";
        }
    }

    cout << "\n=====================================\n";
}