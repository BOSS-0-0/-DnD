#include "ClassCatalog.h"

using namespace std;

void ClassCatalog::addFeature(
    const string& className,
    const ClassFeature& feature
) {
    FeatureClass[className].push_back(feature);
}

vector<ClassFeature> ClassCatalog::featuresAt(
    const string& className,
    int level
) const {
    auto it = FeatureClass.find(className);

    if (it == FeatureClass.end()) {
        return {};
    }

    vector<ClassFeature> result;

    for (const auto& feature : it->second) {
        if (feature.level == level) {
            result.push_back(feature);
        }
    }

    return result;
}

vector<ClassFeature> ClassCatalog::skillsAt(
    const string& className,
    int level
) const {
    auto it = FeatureClass.find(className);

    if (it == FeatureClass.end()) {
        return {};
    }

    vector<ClassFeature> result;

    for (const auto& feature : it->second) {
        if (feature.level == level && !feature.isSpell) {
            result.push_back(feature);
        }
    }

    return result;
}

vector<ClassFeature> ClassCatalog::spellsAt(
    const string& className,
    int level
) const {
    auto it = FeatureClass.find(className);

    if (it == FeatureClass.end()) {
        return {};
    }

    vector<ClassFeature> result;

    for (const auto& feature : it->second) {
        if (feature.level == level && feature.isSpell) {
            result.push_back(feature);
        }
    }

    return result;
}

vector<ClassFeature> ClassCatalog::allFeatures(
    const string& className
) const {
    auto it = FeatureClass.find(className);

    if (it == FeatureClass.end()) {
        return {};
    }

    return it->second;
}

bool ClassCatalog::hasClass(const string& className) const {
    return FeatureClass.find(className) != FeatureClass.end();
}

ClassCatalog createDefaultClassCatalog() {
    ClassCatalog catalog;

    catalog.addFeature("Fighter", {
        "Second Wind",
        "Бонусным действием можно восстановить 1d10 + уровень воина хитов. Используется один раз, восстанавливается после короткого или длительного отдыха.",
        1,
        false
    });

    catalog.addFeature("Fighter", {
        "Action Surge",
        "В свой ход можно получить одно дополнительное действие поверх обычного и бонусного. Восстанавливается после короткого отдыха.",
        2,
        false
    });

    catalog.addFeature("Fighter", {
        "Martial Archetype",
        "На 3-м уровне воин выбирает воинский архетип (например, Champion, Battle Master или Eldritch Knight).",
        3,
        false
    });

    catalog.addFeature("Fighter", {
        "Ability Score Improvement",
        "Можно увеличить одну характеристику на 2 или две на 1, либо взять черту (Feat).",
        4,
        false
    });

    catalog.addFeature("Fighter", {
        "Extra Attack",
        "Воин может атаковать дважды, вместо одного раза, когда совершает действие Атака в свой ход.",
        5,
        false
    });

    catalog.addFeature("Wizard", {
        "Spellcasting",
        "Волшебник использует Интеллект как базовую характеристику для заклинаний и имеет книгу заклинаний.",
        1,
        false
    });

    catalog.addFeature("Wizard", {
        "Fire Bolt",
        "Заговор (cantrip). Метает огненный снаряд на 120 футов. Урон: 1d10 огнём.",
        1,
        true
    });

    catalog.addFeature("Wizard", {
        "Magic Missile",
        "Заклинание 1-го круга. Создаёт 3 светящихся дротика, которые автоматически попадают в цель. Урон: 1d4+1 силовым полем каждый.",
        1,
        true
    });

    catalog.addFeature("Wizard", {
        "Shield",
        "Заклинание 1-го круга (реакция). Даёт +5 к КД до начала следующего хода и блокирует Волшебную стрелу.",
        1,
        true
    });

    catalog.addFeature("Wizard", {
        "Arcane Recovery",
        "Раз в день после короткого отдыха можно восстановить ячейки заклинаний с суммарным уровнем до половины уровня волшебника.",
        2,
        false
    });

    catalog.addFeature("Wizard", {
        "Arcane Tradition",
        "На 3-м уровне выбирает магическую школу (например, Воплощение, Превращение или Ограждение).",
        3,
        false
    });

    catalog.addFeature("Wizard", {
        "Fireball",
        "Заклинание 3-го круга. Взрыв радиусом 20 футов на расстоянии 150 футов. Урон: 8d6 огнём (спасбросок Ловкости уменьшает вдвое).",
        3,
        true
    });

    catalog.addFeature("Wizard", {
        "Ability Score Improvement",
        "Можно увеличить одну характеристику на 2 или две на 1, либо взять черту.",
        4,
        false
    });

    catalog.addFeature("Rogue", {
        "Expertise",
        "Выбирает два навыка (или один навык и воровские инструменты) и удваивает бонус мастерства для них.",
        1,
        false
    });

    catalog.addFeature("Rogue", {
        "Sneak Attack",
        "Раз в ход можно нанести дополнительный урон (1d6 на 1-м уровне), если есть преимущество или цель находится в 5 футах от союзника.",
        1,
        false
    });

    catalog.addFeature("Rogue", {
        "Thieves' Cant",
        "Секретный язык воров, убийц и контрабандистов. Позволяет передавать скрытые сообщения.",
        1,
        false
    });

    catalog.addFeature("Rogue", {
        "Cunning Action",
        "Бонусным действием можно совершить Рывок, Отход или Засаду.",
        2,
        false
    });

    catalog.addFeature("Rogue", {
        "Roguish Archetype",
        "На 3-м уровне выбирает архетип: Вор, Убийца или Мистический ловкач.",
        3,
        false
    });

    catalog.addFeature("Rogue", {
        "Ability Score Improvement",
        "Можно увеличить характеристику или взять черту.",
        4,
        false
    });

    catalog.addFeature("Rogue", {
        "Uncanny Dodge",
        "Реакцией можно уменьшить вдвое урон от атаки, которую плут видит.",
        5,
        false
    });

    return catalog;
}