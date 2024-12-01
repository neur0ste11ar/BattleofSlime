#include "parse.h"

Type stringToType(const string typeStr) {
	static unordered_map<string, Type> typeMap = {
		{"attack", attack},
		{"heal", heal},
		{"weather", weather},
		{"sing", sing},
		{"paint", paint},
	};
	auto it = typeMap.find(typeStr);
	return it != typeMap.end() ? it->second : attack;
}

Element stringToElement(const string elementStr) {
	static unordered_map<string, Element> elementMap = {
		{"normal", normal},
		{"grass", grass},
		{"fire", fire},
		{"water", water},
		{"electric", electric}
	};
	auto it = elementMap.find(elementStr);
	return it != elementMap.end() ? it->second : normal;
}

Weather stringToWeather(const string weatherStr) {
	static unordered_map<string, Weather> weatherMap = {
		{"common", common},
		{"sun", sun},
		{"rain", rain}
	};
	auto it = weatherMap.find(weatherStr);
	return it != weatherMap.end() ? it->second : common;
}

shared_ptr<Skill> initSkill(tinyxml2::XMLElement* skill) {
	string name = skill->FirstChildElement("Name")->GetText();
	Type type = stringToType(skill->FirstChildElement("Type")->GetText());
	Element element = stringToElement(skill->FirstChildElement("Element")->GetText());
	int power = stoi(skill->FirstChildElement("Power")->GetText());
	int priority = stoi(skill->FirstChildElement("Priority")->GetText());
	switch (type) {
		case attack:
			return make_shared<AttackSkill>(name, priority, type, element, power);
		case heal:
			return make_shared<HealSkill>(name, priority, type, element, power);
		case weather:
			return make_shared<WeatherSkill>(name, priority, type, element, power, stringToWeather(skill->FirstChildElement("Weather")->GetText()));
		case sing:
			return make_shared<Sing>(name, priority, type, element, power);
		case paint:
			return make_shared<Paint>(name, priority, type, element, power);
	}
}

map<string, shared_ptr<Skill>> parseSkills(string filename) {
	map<string, shared_ptr<Skill>> skills;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());
	tinyxml2::XMLElement* root = doc.FirstChildElement("Skills");
	for (tinyxml2::XMLElement* skill = root->FirstChildElement("Skill"); skill != NULL; skill = skill->NextSiblingElement("Skill")) {
		string name = skill->FirstChildElement("Name")->GetText();
		skills[name] = initSkill(skill);
	}
	return skills;
}

map<string, shared_ptr<Slime>> parseSlimes(string filename, map<string, shared_ptr<Skill>> skills) {
	map<string, shared_ptr<Slime>> slimes;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());
	tinyxml2::XMLElement* root = doc.FirstChildElement("Slimes");
	for (tinyxml2::XMLElement* slime = root->FirstChildElement("Slime"); slime != NULL; slime = slime->NextSiblingElement("Slime")) {
		string name = slime->FirstChildElement("Name")->GetText();
		Element element = stringToElement(slime->FirstChildElement("Element")->GetText());
		int health = stoi(slime->FirstChildElement("Health")->GetText());
		int attack = stoi(slime->FirstChildElement("Attack")->GetText());
		int defense = stoi(slime->FirstChildElement("Defense")->GetText());
		int speed = stoi(slime->FirstChildElement("Speed")->GetText());
		vector<shared_ptr<Skill>> Slimeskills;
		for (int i = 1; i <= 3; i++) {
			string skillIndex = "Skill" + to_string(i);
			const char* skillIndexCStr = skillIndex.c_str();
			string skillName = slime->FirstChildElement(skillIndexCStr)->GetText();
			Slimeskills.emplace_back(skills[skillName]);
		}
		vector<pair<Status, int>> status = {};
		slimes[name] = make_shared<Slime>(name, element, health, attack, defense, speed, Slimeskills, status, 0);
	}
	return slimes;
}