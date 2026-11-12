#pragma once 
#include <string>
#include <vector>
#include <ClassCatalog.h>
#include <ClassFeature.h>

class HaracterClass{
    private:
    std::string className;
    const ClassCatalog* catalog;
    public:
    HaracterClass(const std::string& className, const ClassCatalog* catalog);
    virtual ~HaracterClass() = default;
    virtual std::string name() const;
    virtual std::vector<ClassFeature> featuresAt(int level) const;
    virtual std::vector<ClassFeature> skillsAt(int level) const;
    virtual std::vector<ClassFeature> skillsAt(int level) const;
    virtual std::vector<ClassFeature> spelsAt(int level) const;
    virtual std::vector<ClassFeature> allFeatures() const;
};
class FighterClass : public HaracterClass {
public:
    explicit FighterClass(const ClassCatalog* catalog);
};
class WizardClass : public HaracterClass {
public:
    explicit WizardClass(const ClassCatalog* catalog);
};

class RogueClass : public HaracterClass {
public:
    explicit RogueClass(const ClassCatalog* catalog);
};
