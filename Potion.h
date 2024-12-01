#pragma once

#include <string>
#include <memory>
#include "Act.h"
#include "Slime.h"
#include "Field.h"

using namespace std;

class Potion :
	public Act
{
	public:
		Potion(string name, int priority) : Act(name, priority) {};
};

class RevivalPotion :
	public Potion
{
	public:
		RevivalPotion(string name, int priority) : Potion(name, priority) {};

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field);
};
