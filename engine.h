#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits>
#include <easy2d/easy2d.h>
#include "parse.h"
#include "Change.h"
#include "Player.h"
#include "Enemy.h"
#include "Field.h"
#include "globalResource.h"

using namespace easy2d;

shared_ptr<Slime> loadPlayer(shared_ptr<Player> player);
shared_ptr<Slime> loadEnemySun(shared_ptr<EnemySun> enemy);
shared_ptr<Slime> loadEnemyRain(shared_ptr<EnemyRain> enemy);

bool sortSequence(Effect& effect1, Effect& effect2);
void execute(Effect& effect, shared_ptr<Field> field, bool& singFlag);

bool checkEnd(shared_ptr<Player> player1, shared_ptr<Player> player2, shared_ptr<Field> field);

Sprite* loadSlimePic(shared_ptr<Slime> slime);
Sprite* loadSlimePic_r(shared_ptr<Slime> slime);
void loadScene(shared_ptr<Field> field);

void playGame(shared_ptr<Player> player1, shared_ptr<Player> player2, shared_ptr<Field> field);