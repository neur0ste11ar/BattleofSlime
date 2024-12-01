#pragma once

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "tinyxml2.h"
#include "Skill.h"
#include "DerivedSkill.h"
#include "Slime.h"
#include "globalResource.h"

using namespace std;

Type stringToType(const string typeStr);
Element stringToElement(const string elementStr);
Weather stringToWeather(const string weatherStr);

shared_ptr<Skill> initSkill(tinyxml2::XMLElement* skill);

map<string, shared_ptr<Skill>> parseSkills(string filename);
map<string, shared_ptr<Slime>> parseSlimes(string filename, map<string, shared_ptr<Skill>> skills);

