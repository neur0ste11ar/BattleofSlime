#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <math.h>
#include "globalResource.h"
#include "Skill.h"

using namespace std;

class Slime
{
	public:
		string name;
		Element element;
		int health;
		int maxHealth;
		int attack;
		int defense;
		int maxDefense;
		int speed;
		vector<shared_ptr<Skill>> skills;
		vector<pair<Status, int>> status;
		int player;

		Slime(string name, Element element, int health, int attack, int defense, int speed, vector<shared_ptr<Skill>> skills, vector<pair<Status, int>> status, int player);
		Slime(const Slime& other);

		string getName() const;
		Element getElement() const;
		int getHealth() const;
		int getMaxHealth() const;
		int getAttack() const;
		int getDefense() const;
		int getMaxDefense() const;
		int getSpeed() const;
		vector<shared_ptr<Skill>> getSkills() const;
		vector<pair<Status, int>> getStatus() const;
		int getPlayer() const;

		void setName(string name);
		void setElement(Element element);
		void setHealth(int health);
		void setMaxHealth(int maxHealth);
		void setAttack(int attack);
		void setDefense(int defense);
		void setMaxDefense(int maxDefense);
		void setSpeed(int speed);
		void setSkills(vector<shared_ptr<Skill>> skills);
		void setStatus(vector<pair<Status, int>> status);
		void setPlayer(int player);

		void printPlayer();
		void printPlayerPotion();
		bool isAlive();
		void takeDamage(int damage);
		void heal(double percent);
		void sleep(int turns);
		bool isSleeping();
		void paint(int turns);
		bool isPainted();
		void updateStatus();
};
