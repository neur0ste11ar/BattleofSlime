#pragma once

#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class EnemySun : 
	public Player
{
	public:
		EnemySun(string name, vector<shared_ptr<Slime>> slimes, map<shared_ptr<Potion>, int> potions) : Player(name, slimes, potions) {};

		Effect selectAct(shared_ptr<Player> player, shared_ptr<Field> field) override;
		void changeSlime(shared_ptr<Field> field) override;
};

class EnemyRain :
	public Player
{
public:
	EnemyRain(string name, vector<shared_ptr<Slime>> slimes, map<shared_ptr<Potion>, int> potions) : Player(name, slimes, potions) {};

	Effect selectAct(shared_ptr<Player> player, shared_ptr<Field> field) override;
	void changeSlime(shared_ptr<Field> field) override;
};

