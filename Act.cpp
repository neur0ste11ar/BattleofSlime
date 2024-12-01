#include "Act.h"

string Act::getName() const
{
	return name;
}

int Act::getPriority() const
{
	return priority;
}

void Act::setName(string name)
{
	this->name = name;
}

void Act::setPriority(int priority)
{
	this->priority = priority;
}

Result Act::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field)
{
	return success;
}