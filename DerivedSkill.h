#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <math.h>
#include "Skill.h"
#include "Slime.h"
#include "Field.h"

double elementMultiplier(Element attacker, Element defender);
double weatherMultiplier(Weather weather, Element attacker);

bool checkStatus(shared_ptr<Slime> self);

shared_ptr<Slime> getTarget(shared_ptr<Slime> self, shared_ptr<Field> field);

class AttackSkill :
    public Skill
{
	public:
		AttackSkill(string name, int priority, Type type, Element element, int power) : Skill(name, priority, type, element, power) {};
		AttackSkill(const AttackSkill& other) : Skill(other) {};

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};

class HealSkill :
	public Skill
{
    public:
		HealSkill(string name, int priority, Type type, Element element, int power) : Skill(name, priority, type, element, power) {};
		HealSkill(const AttackSkill& other) : Skill(other) {};

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};

class WeatherSkill :
	public Skill
{
	public:
		Weather weather;

		WeatherSkill(string name, int priority, Type type, Element element, int power, Weather weather) : Skill(name, priority, type, element, power), weather(weather) {};
		WeatherSkill(const WeatherSkill& other) : Skill(other), weather(other.weather) {};

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};

class Sing :
	public Skill
{
	public:
		Sing(string name, int priority, Type type, Element element, int power) : Skill(name, priority, type, element, power) {};
		Sing(const Sing& other) : Skill(other) {};

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};

class Paint :
	public Skill
{
	public:
		Paint(string name, int priority, Type type, Element element, int power) : Skill(name, priority, type, element, power) {};
		Paint(const Paint& other) : Skill(other) {};

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};
