#pragma once

#include <string>
#include <sstream>
#include <map>
#include <memory>
#include "Change.h"
#include "Slime.h"
#include "Potion.h"
#include "Field.h"
#include "globalResource.h"

using namespace std;

class Player
{
	public:
		string name;
		vector<shared_ptr<Slime>> slimes;
		map<shared_ptr<Potion>, int> potions;

		Player(string name, vector<shared_ptr<Slime>> slimes, map<shared_ptr<Potion>, int> potions);

		string getName() const;
		vector<shared_ptr<Slime>> getSlimes() const;
		map<shared_ptr<Potion>, int> getPotions() const;

		void setName(string name);
		void setSlimes(vector<shared_ptr<Slime>> slimes);
		void setPotions(map<shared_ptr<Potion>, int> potions);

		int aliveNum() const;
		Action selectAction();
		virtual Effect selectAct(shared_ptr<Player> player, shared_ptr<Field> field);
		void usePotion(shared_ptr<Potion> potion);
		virtual void changeSlime(shared_ptr<Field> field);
};