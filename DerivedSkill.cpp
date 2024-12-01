#include "DerivedSkill.h"

using namespace std;

double elementMultiplier(Element attacker, Element defender) {
	static map<pair<Element, Element>, double> multipliers = {
		{{grass, grass}, 0.5}, {{grass, water}, 2.0}, {{grass, fire}, 0.5},
		{{water, grass}, 0.5}, {{water, water}, 0.5}, {{water, fire}, 2.0},
		{{fire, grass}, 2.0}, {{fire, water}, 0.5}, {{fire, fire}, 0.5},
		{{electric, grass}, 0.5}, {{electric, water}, 2.0}, {{electric, electric}, 0.5}
	};
	auto it = multipliers.find({ attacker, defender });
	return it != multipliers.end() ? it->second : 1.0;
}

double weatherMultiplier(Weather weather, Element attacker) {
	static map<pair<Weather, Element>, double> multipliers = {
		{{sun, fire}, 1.5}, {{sun, water}, 0.5},
		{{rain, water}, 1.5}, {{rain, fire}, 0.5},
	};
	auto it = multipliers.find({ weather, attacker });
	return it != multipliers.end() ? it->second : 1.0;
}

bool checkStatus(shared_ptr<Slime> self) {
	if (!self->isAlive()) {
		return false;
	}
	if (self->isSleeping()) {
		self->printPlayer();
		cout << self->getName() << " is sleeping";
		return false;
	}
	return true;
}

shared_ptr<Slime> getTarget(shared_ptr<Slime> self, shared_ptr<Field> field) {
	return self->getPlayer() == 1 ? field->getSlimes().second : field->getSlimes().first;
}

Result AttackSkill::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) {
	if (!checkStatus(self)) {
		return failure;
	}
	self->printPlayer();
	cout << self->getName() << " uses " << name << "! ";
	target = getTarget(self, field);
	double multiplier1 = elementMultiplier(element, target->getElement());
	double multiplier2 = weatherMultiplier(field->getWeather().first, element);
	double multiplier3 = (name == "Slap" && target->isSleeping() ? 2.0 : 1.0);
	double multiplier4 = 1.0;
	if (name == "Thunder") {
		if (field->getWeather().first == rain) {
			multiplier4 = 2.0;
		}
		else {
			cout << "Failure!";
			return failure;
		}
	}
	double multiplier = multiplier1 * multiplier2 * multiplier3 * multiplier4;
	int damage = round(double(self->getAttack()) / double(target->getDefense()) * double(power) * multiplier);
	target->takeDamage(damage);
	return success;
}

Result HealSkill::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) {
	if (!checkStatus(self)) {
		return failure;
	}
	self->printPlayer();
	cout << self->getName() << " uses " << name << "! ";
	target = self;
	double healing = double(power) / 100;
	if (name == "Synthesis") {
		switch(field->getWeather().first) {
			case common:
				healing = 0.3;
				break;
			case sun:
				healing = 0.4;
				break;
			case rain:
				healing = 0.2;
				break;
		}
	}
	target->heal(healing);
	return success;
}

Result WeatherSkill::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) {
	if (!checkStatus(self)) {
		return failure;
	}
	self->printPlayer();
	cout << self->getName() << " uses " << name << "! ";
	field->changeWeather(weather, power);
	return success;
}

Result Sing::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) {
	if (!checkStatus(self)) {
		return failure;
	}
	self->printPlayer();
	cout << self->getName() << " uses " << name << "! ";
	target = getTarget(self, field);
	if (!target->isSleeping()) {
		target->sleep(power);
	}
	else {
		cout << "Waste!";
		return waste;
	}
	return success;
}

Result Paint::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) {
	if (!checkStatus(self)) {
		return failure;
	}
	self->printPlayer();
	cout << self->getName() << " uses " << name << "! ";
	target = getTarget(self, field);
	if (!target->isPainted()) {
		target->paint(power);
	}
	else {
		cout << "Waste!";
		return waste;
	}
	return success;
}