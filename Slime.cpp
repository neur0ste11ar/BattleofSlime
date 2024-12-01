#include "Slime.h"

using namespace std;

Slime::Slime(string name, Element element, int health, int attack, int defence, int speed, vector<shared_ptr<Skill>> skills, vector<pair<Status, int>> status, int player) {
	this->name = name;
	this->element = element;
	this->health = health;
	this->maxHealth = health;
	this->attack = attack;
	this->defense = defence;
	this->maxDefense = defence;
	this->speed = speed;
	this->skills = skills;
	this->status = status;
	this->player = player;
}

Slime::Slime(const Slime& other)
	: name(other.name), element(other.element), health(other.health),
	maxHealth(other.maxHealth), attack(other.attack), defense(other.defense),
	maxDefense(other.maxDefense), speed(other.speed), status(other.status),
	player(other.player) {
	for (const auto& skill : other.skills) {
		skills.emplace_back(make_shared<Skill>(*skill));
	}
}

string Slime::getName() const {
	return name;
}

Element Slime::getElement() const {
	return element;
}

int Slime::getHealth() const {
	return health;
}

int Slime::getMaxHealth() const {
	return maxHealth;
}

int Slime::getAttack() const {
	return attack;
}

int Slime::getDefense() const {
	return defense;
}

int Slime::getMaxDefense() const {
	return maxDefense;
}

int Slime::getSpeed() const {
	return speed;
}

vector<shared_ptr<Skill>> Slime::getSkills() const {
	return skills;
}

vector<pair<Status, int>> Slime::getStatus() const {
	return status;
}

int Slime::getPlayer() const {
	return player;
}

void Slime::setName(string name) {
	this->name = name;
}

void Slime::setElement(Element element) {
	this->element = element;
}

void Slime::setHealth(int health) {
	this->health = health;
}

void Slime::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}

void Slime::setAttack(int attack) {
	this->attack = attack;
}

void Slime::setDefense(int defense) {
	this->defense = defense;
}

void Slime::setMaxDefense(int maxDefense) {
	this->maxDefense = maxDefense;
}

void Slime::setSpeed(int speed) {
	this->speed = speed;
}

void Slime::setSkills(vector<shared_ptr<Skill>> skills) {
	this->skills = skills;
}

void Slime::setStatus(vector<pair<Status, int>> status) {
	this->status = status;
}

void Slime::setPlayer(int player) {
	this->player = player;
}

void Slime::printPlayer() {
	if (player == 1) {
		cout << "Your ";
	}
	else if (player == 2)
		cout << "Enemy's ";
}

void Slime::printPlayerPotion() {
	if (player == 1) {
		cout << "You use";
	}
	else if (player == 2)
		cout << "Enemy uses";
}

bool Slime::isAlive() {
	return health > 0;
}

void Slime::takeDamage(int damage) {
	cout << "Damage: " << damage;
	health -= damage;
	if (health < 0) {
		health = 0;
	}
	for (int i = 0; i < status.size(); i++) {
		if (status[i].first == asleep) {
			status.erase(status.begin() + i);
			cout << endl;
			printPlayer();
			cout << name << " wakes up";
		}
	}
}

void Slime::heal(double percent) {
	int recovery =  round(maxHealth * percent);
	cout << "Recovery: " << recovery;
	health += recovery;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

void Slime::sleep(int turns) {
	printPlayer();
	cout << name << " falls asleep";
	pair<Status, int> sleep = make_pair(asleep, turns);
	status.emplace_back(sleep);
}

bool Slime::isSleeping() {
	for (int i = 0; i < status.size(); i++) {
		if (status[i].first == asleep) {
			return true;
		}
	}
	return false;
}

void Slime::paint(int turns) {
	printPlayer();
	cout << name << " is painted";
	defense = round(double(maxDefense) / 2);
	pair<Status, int> paint = make_pair(painted, turns);
	status.emplace_back(paint);
}

bool Slime::isPainted() {
	for (int i = 0; i < status.size(); i++) {
		if (status[i].first == painted) {
			return true;
		}
	}
	return false;
}

void Slime::updateStatus() {
	for (int i = 0; i < status.size(); i++) {
		status[i].second--;
		if (status[i].second == 0) {
			printPlayer();
			switch(status[i].first) {
				case asleep:
					cout << name << " wakes up" << endl;
					break;
				case painted:
					cout << name << " is no longer painted" << endl;
					break;
			}
			status.erase(status.begin() + i);
		}
	}
}