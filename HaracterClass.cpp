#include "HaracterClass.h"

using namespace std;

HaracterClass::HaracterClass(const std::string& className,const ClassCatalog* catalog) : className(className),catalog(catalog) {}

std::string HaracterClass::name() const {
    return className;
}

std::vector<ClassFeature> HaracterClass::featuresAt(int level) const {
    if (!catalog) {
        return {};
    }

    return catalog->featuresAt(className, level);
}

std::vector<ClassFeature> HaracterClass::skillsAt(int level) const {
    if (!catalog) {
        return {};
    }

    return catalog->skillsAt(className, level);
}

vector<ClassFeature> HaracterClass::spelsAt(int level) const {
    if (!catalog) {
        return {};
    }

    return catalog->spellsAt(className, level);
}

vector<ClassFeature> HaracterClass::allFeatures() const {
    if (!catalog) {
        return {};
    }

    return catalog->allFeatures(className);
}

FighterClass::FighterClass(const ClassCatalog* catalog) : HaracterClass("Fighter", catalog) {}

WizardClass::WizardClass(const ClassCatalog* catalog) : HaracterClass("Wizard", catalog) {}

RogueClass::RogueClass(const ClassCatalog* catalog) : HaracterClass("Rogue", catalog) {}