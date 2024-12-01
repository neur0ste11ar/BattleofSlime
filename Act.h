#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "globalResource.h"

class Slime;
class Field;

using namespace std;

class Act
{
	public:
		string name;
		int priority;

		Act(string name, int priority) : name(name), priority(priority) {};
		Act(const Act& other) : name(other.name), priority(other.priority) {};

		string getName() const;
		int getPriority() const;

		void setName(string name);
		void setPriority(int priority);

		virtual Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field);
};

typedef struct {
	Action action;
	shared_ptr<Act> act;
	shared_ptr<Slime> self;
	shared_ptr<Slime> target;
	shared_ptr<Field> field;
}Effect;

