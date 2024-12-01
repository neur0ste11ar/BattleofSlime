#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include "globalResource.h"
#include "Slime.h"

using namespace std;

class Field
{
	public:
		int turns;
		pair<Weather, int> weather;
		pair<shared_ptr<Slime>, shared_ptr<Slime>> slimes;

		Field(int turns, pair<Weather, int> weather, pair<shared_ptr<Slime>, shared_ptr<Slime>> slimes) : turns(turns), weather(weather), slimes(slimes) {};

		int getTurns() const;
		pair<Weather, int> getWeather() const;
		pair<shared_ptr<Slime>, shared_ptr<Slime>> getSlimes() const;

		void setTurns(int turns);
		void setWeather(pair<Weather, int> weather);
		void setSlimes(pair<shared_ptr<Slime>, shared_ptr<Slime>> slimes);

		void printHealth();
		void changeWeather(Weather weather, int turns);
		void updateWeather();
		void updateField();
};

string weatherToString(Weather weather);
