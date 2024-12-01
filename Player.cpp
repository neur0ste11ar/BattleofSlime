#include "Player.h"

using namespace std;

Player::Player(string name, vector<shared_ptr<Slime>> slimes, map<shared_ptr<Potion>, int> potions)
{
	this->name = name;
	this->slimes = slimes;
	this->potions = potions;
}

string Player::getName() const
{
	return name;
}

vector<shared_ptr<Slime>> Player::getSlimes() const
{
	return slimes;
}

map<shared_ptr<Potion>, int> Player::getPotions() const
{
	return potions;
}

void Player::setName(string name)
{
	this->name = name;
}

void Player::setSlimes(vector<shared_ptr<Slime>> slimes)
{
	this->slimes = slimes;
}

void Player::setPotions(map<shared_ptr<Potion>, int> potions)
{
	this->potions = potions;
}

int Player::aliveNum() const
{
	int count = 0;
	for (const auto& slime : slimes)
	{
		if (slime->isAlive())
		{
			count++;
		}
	}
	return count;
}

Action Player::selectAction()
{
	if (aliveNum() == 1)
	{
		cout << "Select your action (0 for escape, 1 for skill): ";
	}
	else if (aliveNum() > 1)
	{
		cout << "Select your action (0 for escape, 1 for skill, 2 for change): ";
	}
	int action;
	cin >> action;
	if (cin.fail() || action < escape || action > change) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return selectAction();
	}
	return static_cast<Action>(action);
}

Effect Player::selectAct(shared_ptr<Player> player, shared_ptr<Field> field)
{
	bool flag;
	Effect effect;
	do {
		flag = false;
		Action action = selectAction();
		shared_ptr<Slime> self = field->getSlimes().first;
		switch (action) {
		case escape: {
			effect = { escape, make_shared<Act>("Escape", 8), self, nullptr, nullptr };
			return effect;
		}
		case skill: {
			stringstream ss;
			ss << "Select the skill (0 for back, ";
			vector<shared_ptr<Skill>> skills = self->getSkills();
			for (int i = 0; i < skills.size(); i++) {
				ss << i + 1 << " for " << skills[i]->getName();
				if (i < skills.size() - 1) {
					ss << ", ";
				}
			}
			ss << "): ";
			while (true) {
				cout << ss.str();
				int index;
				cin >> index;
				if (cin.fail() || index < 0 || index > skills.size()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else if (index == 0) {
					flag = true;
					break;
				}
				else {
					effect = { skill, skills[index - 1], self, nullptr, nullptr };
					return effect;
				}
			}
			break;
		}
		case change: {
			stringstream ss;
			ss << "Select your next slime (0 for back, ";
			vector<int> aliveIndex;
			for (int i = 0; i < slimes.size(); i++) {
				if (slimes[i]->isAlive() && slimes[i] != field->getSlimes().first) {
					ss << i + 1 << " for " << slimes[i]->getName() << "-HP" << slimes[i]->getHealth() << ", ";
					aliveIndex.emplace_back(i + 1);
				}
			}
			string s = ss.str();
			s = s.substr(0, s.size() - 2);
			while (true) {
				cout << s << "): ";
				int index;
				cin >> index;
				if (cin.fail() || (find(aliveIndex.begin(), aliveIndex.end(), index) == aliveIndex.end() && index != 0)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else if (index == 0) {
					flag = true;
					break;
				}
				else {
					effect = { change, make_shared<Change>("Change", 6), self, slimes[index - 1], nullptr };
					return effect;
				}
			}
			break;
		}
		}
	} while (flag);
}

void Player::usePotion(shared_ptr<Potion> potion)
{
	if (potions[potion] > 0) {
		potions[potion]--;
	}
}

void Player::changeSlime(shared_ptr<Field> field)
{
	stringstream ss;
	ss << "Select your next slime (";
	vector<int> aliveIndex;
	for (int i = 0; i < slimes.size(); i++) {
		if (slimes[i]->isAlive() && slimes[i] != field->getSlimes().first) {
			ss << i + 1 << " for " << slimes[i]->getName() << "-HP" << slimes[i]->getHealth() << ", ";
			aliveIndex.emplace_back(i + 1);
		}
	}
	string s = ss.str();
	s = s.substr(0, s.size() - 2);
	while (true) {
		cout << s << "): ";
		int index;
		cin >> index;
		if (cin.fail() || find(aliveIndex.begin(), aliveIndex.end(), index) == aliveIndex.end()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else {
			shared_ptr<Act> change = make_shared<Change>("Change", 6);
			change->activate(field->getSlimes().first, slimes[index - 1], field);
			break;
		}
	}
}