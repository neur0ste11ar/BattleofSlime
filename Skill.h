#pragma once

#include <string>
#include <memory>
#include "globalResource.h"
#include "Act.h"

using namespace std;

class Skill :
	public Act
{
	public:
		Type type;
		Element element;
		int power;

		Skill(string name, int priority, Type type, Element element, int power) : Act(name, priority), type(type), element(element), power(power) {};
		Skill(const Skill& other) : Act(other), type(other.type), element(other.element), power(other.power) {};

		Type getType() const;
		Element getElement() const;
		int getPower() const;
		void setType(Type type);
		void setElement(Element element);
		void setPower(int power);

		Result activate(shared_ptr<Slime> self, shared_ptr<Slime> target, shared_ptr<Field> field) override;
};
