#include "Field.h"

using namespace std;

int Field::getTurns() const {
	return turns;
}

pair<Weather, int> Field::getWeather() const {
	return weather;
}

pair<shared_ptr<Slime>, shared_ptr<Slime>> Field::getSlimes() const {
	return slimes;
}

void Field::setTurns(int turns) {
	this->turns = turns;
}

void Field::setWeather(pair<Weather, int> weather) {
	this->weather = weather;
}

void Field::setSlimes(pair<shared_ptr<Slime>, shared_ptr<Slime>> slimes) {
	this->slimes = slimes;
} 

void Field::printHealth() {
	cout << "Your " << slimes.first->getName() << ": HP " << slimes.first->getHealth() <<  "||" << "Enemy's " << slimes.second->getName() << ": HP " << slimes.second->getHealth() << endl;
}

void Field::changeWeather(Weather weather, int turns) {
	cout << "Weather becomes " << weatherToString(weather);
	this->weather = make_pair(weather, turns);
}

void Field::updateWeather() {
	if (weather.first != common) {
		weather.second--;
		if (weather.second == 0) {
			cout << "Weather becomes normal" << endl;
			weather.first = common;
		}
	}
}

void Field::updateField()
{
	slimes.first->updateStatus();
	slimes.second->updateStatus();
	updateWeather();
}

string weatherToString(Weather weather) {
	switch(weather) {
		case common:
			return "common";
		case sun:
			return "sun";
		case rain:
			return "rain";
	}
}