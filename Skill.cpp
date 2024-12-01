#include "Skill.h"

using namespace std;

Type Skill::getType() const {
	return type;
}

Element Skill::getElement() const {
	return element;
}

int Skill::getPower() const {
	return power;
}

void Skill::setType(Type type) {
	this->type = type;
}

void Skill::setElement(Element element) {
	this->element = element;
}

void Skill::setPower(int power) {
	this->power = power;
}

Result Skill::activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) {
	return success;
}