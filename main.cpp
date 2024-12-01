#include <iostream>
#include "engine.h"

using namespace easy2d;

int main() {
		cout << "Welcome to Battle of Slimes 2!" << endl;

		shared_ptr<RevivalPotion> revivalPotion = make_shared<RevivalPotion>("RevivalPotion", 5);
		shared_ptr<Player> player = make_shared<Player>(
			"player",
			vector<shared_ptr<Slime>>{},
			map<shared_ptr<Potion>, int>{}
		);
		shared_ptr<EnemySun> enemy = make_shared<EnemySun>(
			"enemy",
			vector<shared_ptr<Slime>>{},
			map<shared_ptr<Potion>, int>{{revivalPotion, 1}}
		);
		shared_ptr<Slime> enemyFirst = loadEnemySun(enemy);
		shared_ptr<Slime> playerFirst = loadPlayer(player);
		shared_ptr<Field> field = make_shared<Field>(
			0,
			make_pair(common, 100),
			make_pair(playerFirst, enemyFirst)
		);

		field->printHealth();
		cout << "Battle starts!\n--------------------------------------------------\n";

		playGame(player, enemy, field);
	return 0;
}