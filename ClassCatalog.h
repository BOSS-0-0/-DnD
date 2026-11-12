#pragma once

#include <string>
#include <map>
#include <vector>

#include "ClassFeature.h"

class ClassCatalog {
private:
    std::map<std::string, std::vector<ClassFeature>> FeatureClass;

public:
    void addFeature(const std::string& className,const ClassFeature& feature);
    std::vector<ClassFeature> featuresAt(const std::string& className,int level) const;
    std::vector<ClassFeature> skillsAt(const std::string& className,int level) const;
    std::vector<ClassFeature> spellsAt(const std::string& className,int level) const;
    std::vector<ClassFeature> allFeatures(const std::string& className) const;
    bool hasClass(const std::string& className) const;
};
ClassCatalog createDefaultClassCatalog();